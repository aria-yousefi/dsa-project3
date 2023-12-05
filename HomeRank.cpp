#include "HomeRank.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function for reading data from CSV file and storing data points in homeData map.
void HomeRank::extractData(string dir)
{
	ifstream file;
	file.open(dir);

	vector<string> dataPoints;
	string address;
	string row, t;
	getline(file, row);

	while (file.good())
	{
		dataPoints.clear();
		int count = 0;
		getline(file, row);
		stringstream line(row);
		while (line.good())
		{
			/* 2nd column of CSV indicates the home address. If this is being accessed, store the address
			in a string to later use as a key when inserting data into the homeData map */
			if (count == 1)
			{
				getline(line, address, ',');
			}

			// Store all other data in a vector which will be inserted in the homeData map as a value
			else
			{
				string word;
				getline(line, word, ',');
				dataPoints.push_back(word);
			}

			count++;
		}

		homeData[address] = dataPoints;
	}

	file.close();
}

// Function for calculating and assigning scores to each home in homeData based on user's preferences
void HomeRank::calculateScores() {
	unordered_map<string, vector<string>>::iterator it;
	for (it = homeData.begin(); it != homeData.end(); it++) { //Iterate through every single home in home data
		float scoreTotal = 1;

		scoreTotal += userProfileWeights[1] * (stof(it->second[5])) / userProfile[1]; //Beds
		scoreTotal += userProfileWeights[2] * (stof(it->second[6])) / userProfile[2]; //Baths
		scoreTotal += userProfileWeights[3] * (stof(it->second[7])) / userProfile[3]; //Sq Feet

		if (((stof(it->second[4])) >= userProfile[0] * 0.8) && (((stof(it->second[4])) //Pass, Fail system where if house is too far out of price range, it is excluded
			<= (userProfile[0] * 1.1)))) {
			scoreTotal *= userProfile[0] / (stof(it->second[4])); //If house is in data range then it is given a score for its price
		}
		else {
			scoreTotal = 0;
		}

		if ((stof(it->second[8])) < userProfile[4]) {
			scoreTotal = 0;
		}

		pair<string, float> tempPair = { it->first, scoreTotal };
		scores1.push_back(tempPair);
	}
	scores2 = scores1;
}

// Source: Module 6 Sorting Presentation
//Function for merging vectors during merge sort process
void HomeRank::merge(vector<pair<string, float>>& scrs, int left, int mid, int right) {
	
	//Create two seperate vectors from left - mid and then mid + 1 to right
	int n1 = mid - left + 1;
	int n2 = right - mid;
	vector<pair<string, float>> x(n1);
	vector<pair<string, float>> y(n2);

	for (int i = 0; i < n1; i++) {
		x[i] = scrs[left + i];
	}
	for (int j = 0; j < n2; j++) {
		y[j] = scrs[mid + 1 + j];
	}

	//Put and x and y together into one vector
	int i, j, k;
	i = 0;
	j = 0;
	k = left;


	while (i < n1 && j < n2) {
		if (x[i].second <= y[j].second) {
			scrs[k] = x[i];
			i++;
		}
		else
		{
			scrs[k] = y[j];
			j++;
		}
		k++;
	}
	//If we run out of elements in x or y then simply append remaining elements in other vector
	while (i < n1) {
		scrs[k] = x[i];
		i++;
		k++;
	}
	while (j < n2) {
		scrs[k] = y[j];
		j++;
		k++;
	}
}

// Source: Module 6 Sorting Presentation
//Function for executing merge sort
void HomeRank::mergeSort(vector<pair<string, float>>& scrs, int left, int right) {
	if (left < right) {
		// Identify middle index
		int middle = left + (right - left) / 2;
		// Recursively call mergesort() function on left and right subarrays
		mergeSort(scrs, left, middle);
		mergeSort(scrs, middle + 1, right);
		// Call merge() function to perform merging of subarrays
		merge(scrs, left, middle, right);
	}
}

// Source: Module 6 Sorting Presentation
//Partition function for quick sort does swapping of elements around pivot
int HomeRank::partition(vector<pair<string, float>>& scrs, int low, int high) // 
{

	float pivot = scrs[low].second; //Set pivot position to low element in vector

	int up = low, down = high;
	while (up < down) { //While up index is less then down index iterate both and swap
		for (int j = up; j < high; j++) {

			if (scrs[up].second > pivot) {
				break;
			}
			up++;
		}
		for (int j = high; j > low; j--) {
			if (scrs[down].second < pivot) {
				break;
			}
			down--;
		}
		if (up < down) {
			swap(scrs[up], scrs[down]); 
		}
	}
	swap(scrs[low], scrs[down]); 
	return down; //This will be our new pivot position
}

//Function for executing quick sort
void HomeRank::quickSort(vector<pair<string, float>>& scrs, int low, int high) {
	while (low < high) {
		int pivot = partition(scrs, low, high); //Set pivot to partition

		if (pivot - low <= high - (pivot+1)) { 
			quickSort(scrs, low, pivot); //Call quickSort recursively on vector from low - pivot
			low = pivot + 1;
		}
		else {
			quickSort(scrs, pivot + 1, high); //Call quicksort recursively on vector from pivot + 1 - high
			high = pivot;
		}
	}
}



// Public mergesort helper function which returns the sort's runtime as an int in microseconds
int HomeRank::helperMergeSort()
{
	auto start = high_resolution_clock::now();
	mergeSort(scores1, 0, scores1.size() - 1);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	return duration.count();
}

// Public quicksort helper function which returns the sort's runtime as an int in microseconds
int HomeRank::helperQuickSort()
{
	auto start = high_resolution_clock::now();
	quickSort(scores2, 0, scores2.size() - 1);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	return duration.count();
}

// Public helper function for adding user input values into userProfile vector
void HomeRank::addToUserProfile(float ans)
{
	userProfile.push_back(ans);
}

// Public helper function for adding user input "weights" based on significance of each variable into userProfileWeights vector
void HomeRank::addToUserProfileWeights(float rate)
{
	userProfileWeights.push_back(rate);
}

// Public helper function for outputting top 10 homes alongside other info based on the user's answers
void HomeRank::outputTop10() //Not used in program, but used to debug program
{
	for (int i = 0; i < 10; i++)
	{
		cout << i + 1 << ". " << scores1[i].first << ", " << homeData[scores1[i].first][1]
			<< ", " << homeData[scores1[i].first][2] << ", " << homeData[scores1[i].first][3] << endl
			<< "Price: $" << homeData[scores1[i].first][4] << " | Beds/Baths: " << homeData[scores1[i].first][5]
			<< '/' << homeData[scores1[i].first][6] << " | Sq. Ft: " << homeData[scores1[i].first][7]
			<< " | Year Built: " << homeData[scores1[i].first][8] << endl << endl;
	}
}

//Public function to get nth highest scoring house after the sort function has been called. This function uses merge sort.
string HomeRank::stringOutput(int n)
{
	string output = "";
	int i = scores1.size() - n - 1;
	output = scores1[i].first + ", " + homeData[scores1[i].first][1]
		+ ", " + homeData[scores1[i].first][2] + ", " + homeData[scores1[i].first][3] + " | "
		+ "Price: $" + homeData[scores1[i].first][4] + " | Beds/Baths: " + homeData[scores1[i].first][5]
		+ '/' + homeData[scores1[i].first][6] + " | Sq. Ft: " + homeData[scores1[i].first][7]
		+ " | Year Built: " + homeData[scores1[i].first][8];
	return output;
}

string HomeRank::stringOutput2(int n) //Used for debug purposes. Public function to get nth highest scoring house after the sort function has been called. This function uses quick sort.
{
	string output = "";
	int i = scores2.size() - n - 1;
	output = scores2[i].first + ", " + homeData[scores2[i].first][1]
		+ ", " + homeData[scores2[i].first][2] + ", " + homeData[scores2[i].first][3] + " | "
		+ "Price: $" + homeData[scores2[i].first][4] + " | Beds/Baths: " + homeData[scores2[i].first][5]
		+ '/' + homeData[scores2[i].first][6] + " | Sq. Ft: " + homeData[scores2[i].first][7]
		+ " | Year Built: " + homeData[scores2[i].first][8];
	return output;
}