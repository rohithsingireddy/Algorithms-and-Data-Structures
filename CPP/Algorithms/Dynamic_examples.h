 #include <vector>
 #include <string>
 #include <climits>

 namespace Dynamic {

	/*
	* Takes array of prices of every length and the maximum length as input
	* Assumes price array has price of every lenght including zero and max_length
	* Returns a vector with maximum price that can be obtained at zero index and the possible
	* lengths associated with that price in the following indices
	*/
	std::vector<int> max_price_for_rod(int* price_of_length, int max_length) {
		// max_price( length ) = max_price(k) + max_price(lenght-k)
		

		int* dp_array = new int[max_length + 1];
		int* cut_off = new int [max_length + 1];

		for( int i = 0; i <= max_length; i++ ) {
			dp_array[i] = price_of_length[i];
			cut_off[i] = i;
		}

		for( int cut = 0; cut <= max_length; cut++ ) {
			
			for( int length = cut; length <= max_length; length++) {

				if ( dp_array[length] < dp_array[length-cut] + dp_array[cut] ) {

					dp_array[length] = dp_array[length-cut] + dp_array[cut];
					cut_off[length] = cut;
				}
			}
  		}
		
		std::vector<int> result;
		result.push_back(dp_array[max_length]);
		int cut = max_length;
		while( cut > 0 ) {
			result.push_back(cut_off[cut]);			
			cut -= cut_off[cut];

		}
		return result;
	}

	/*
	 * Common Subsequence Problem
	 * Finds the common subsequences between two strings and returns them in a vector
	 * Should correct for input abracadabraemalesmagic abracadabrayfemalemagic
	 */
	std::vector<std::string> common_subsequence(std::string string_1, std::string string_2) {
		int size_1 = string_1.length();
		int size_2 = string_2.length();

		std::string result = "";
		std::vector<std::string> strings;

		int** string_matrix = new int*[ size_1 +1 ];

		for( int i = 0; i <= size_1; i++ ) {
			string_matrix[i] = new int[size_2 + 1];
			for( int j = 0; j <= size_2; j++ ) {
				string_matrix[i][j] = 0;
			}
		}

		for( int i = 1; i <= size_1; i++ ) {

			for( int j = 1; j <= size_2; j++) {
				
				if( string_1[i-1] == string_2[j-1] ) {
					string_matrix[i][j] = 1 + string_matrix[i-1][j-1];
				}
				else {
					string_matrix[i][j] = std::max(string_matrix[i][j-1], string_matrix[i-1][j]);
				}
			}
		}

		int i = size_1,  j = size_2;

		auto reverse_string = [](std::string& result) {
					int last_index = result.length() - 1;
					int limit = result.length() / 2;
					for( int i = 0; i < limit; i++ ) {
						std::swap(result[i], result[last_index - i]);
					}
					return result;
		};

		while(i > 0 && j > 0) {
			if( string_1[i - 1] == string_2[j - 1] ) {
				result += string_1[i - 1];
				i--;j--;
			}
			else {
				if( !result.empty() ) {
					strings.push_back(reverse_string(result));
					result = "";
				}
				if( string_matrix[i-1][j] > string_matrix[i][j-1] ) {
					i--;
				}
				else {
					j--;
				}
			}
		}
		strings.push_back(reverse_string(result));		
		return strings;
	} 

 }

