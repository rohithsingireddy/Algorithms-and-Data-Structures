#include <vector>
#include <functional>
#include <climits>

namespace D_and_C
{
    /** 
     * Solves the max-subarray problem using divide and conquer
     * Returns a vector of size 3 with the sum, left and right indices of sub-array
     * Kadane's algorithm has better time complexity than this ( linear time complexity)
     * 
     * Time Complexity = O( n log(n) )
     * Space Complexity = O( log(n) )
     */
    std::vector<int> max_sub_array_sum(const std::vector<int> &array)
    {
        std::function<std::vector<int>(int, int, int)> conquer =
            [&array](int left, int mid, int right) -> std::vector<int>
        {
            int left_sum = INT_MIN, right_sum = INT_MIN;
            int max_left = mid, max_right = mid;

            int sum = 0;
            for (int i = mid; i >= left; i--)
            {
                sum += array[i];
                if (sum >= left_sum)
                {
                    left_sum = sum;
                    max_left = i;
                }
            }

            sum = 0;
            for (int i = mid + 1; i <= right; i++)
            {
                sum += array[i];
                if (sum >= right_sum)
                {
                    right_sum = sum;
                    max_right = i;
                }
            }

            return std::vector<int>{left_sum + right_sum, max_left, max_right};
        };

        std::function<std::vector<int>(int, int)> divide =
            [&array, &divide, &conquer](int left, int right) -> std::vector<int>
        {
            if (left == right)
            {
                return std::vector<int>{array[left], left, right};
            }
            else
            {
                int mid = (left + right) / 2;
                std::vector<int> left_sum = divide(left, mid);
                std::vector<int> right_sum = divide(mid + 1, right);
                std::vector<int> mid_sum = conquer(left, mid, right);

                std::vector<int> returned_sum = left_sum;

                if (returned_sum[0] < right_sum[0])
                {
                    returned_sum = right_sum;
                }

                if (returned_sum[0] < mid_sum[0])
                {
                    returned_sum = mid_sum;
                }
                return returned_sum;
            }
        };

        return divide(0, array.size() - 1);
    }
}