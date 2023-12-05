#pragma once
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
using namespace std;
using namespace std::chrono;

class HomeRank
{
private:
	unordered_map<string, vector<string>> homeData; 
	vector<pair<string, float>> scores1; 
	vector<pair<string, float>> scores2;
	vector <float> userProfile;
	vector<float> userProfileWeights;
	void extractData(string dir);
	void merge(vector<pair<string, float>>& scrs, int left, int mid, int right); //Merge function for merge sort
	void mergeSort(vector<pair<string, float>>& scrs, int left, int right); //Function for doing merge sort
	int partition(vector<pair<string, float>> &scrs, int low, int high); //Partition function for swapping elements around pivot in quick sort
	void quickSort(vector<pair<string, float>>& scrs, int low, int high); //Function for executing quick sort

public:
	HomeRank(string csvDir) // Function for reading data from CSV file and storing data points in homeData map.
	{
		extractData(csvDir); //Function for reading csv file
	}
	
	int helperMergeSort(); //Function calling merge sort and timing it
	int helperQuickSort(); //Function calling quick sort and timing it
	void addToUserProfile(float ans); // Public helper function for adding user input values into userProfile vector
	void addToUserProfileWeights(float rate); // Public helper function for adding user input "weights" based on significance of each variable into userProfileWeights vector
	void calculateScores(); // Function for calculating and assigning scores to each home in homeData based on user's preferences
	void outputTop10(); // Public helper function for outputting top 10 homes alongside other info based on the user's answers. Used for debug purposes
	string stringOutput(int n); //Public function to get nth highest scoring house after the sort function has been called. This function uses merge sort.
	string stringOutput2(int n); //Used for debug purposes. Public function to get nth highest scoring house after the sort function has been called. This function uses quick sort.
};

