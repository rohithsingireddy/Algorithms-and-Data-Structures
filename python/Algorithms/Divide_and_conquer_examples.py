from math import inf

def max_sub_array_sum(array:list):
    
    def conquer(left:int, mid:int, right:int) -> tuple:
        left_sum, right_sum = -inf, -inf
        max_left, max_right = mid, mid

        s = 0
        for i in range(mid, left - 1, -1):
            s += array[i]
            if s >= left_sum:
                left_sum = s
                max_left = i
        
        s = 0
        for i in range(mid + 1, right + 1):
            s += array[i]
            if s >= right_sum:
                right_sum = s
                max_right = i
        
        return left_sum + right_sum, max_left, max_right

    def divide(left:int, right:int) -> tuple:
        if left == right:
            return array[left], left, left
        else:
            mid = (left + right) // 2
            left_sum = divide(left, mid)
            right_sum = divide(mid + 1, right)
            mid_sum = conquer(left, mid, right)

            returned_sum = left_sum
            if returned_sum[0] < right_sum[0]:
                returned_sum = right_sum
            
            if returned_sum[0] < mid_sum[0]:
                returned_sum = mid_sum
            
            return returned_sum
    
    return divide(0, len(array) - 1)


if __name__ == '__main__':
    aray = [int(x) for x in input().split()]
    print(max_sub_array_sum(aray))
