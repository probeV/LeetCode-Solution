#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        int n = nums.size();
        long long answer = 0;

        vector<int> sum(n, 0);
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                sum[i] = (nums[i] % modulo == k) ? 1 : 0;
            } else {
                sum[i] = sum[i-1] + ((nums[i] % modulo == k) ? 1 : 0);
            }
        }

        // countMap: sum[i] % modulo 값을 저장하는 해시맵
        unordered_map<int, long long> countMap;
        
        // 초기 상태: sum[-1]이 0이라고 가정 (빈 구간)
        countMap[0] = 1;

        for (int i = 0; i < n; ++i) {
            // 현재까지 누적된 sum[i]
            int currentSum = sum[i];
            
            // 현재 sum[i] % modulo
            int currentMod = currentSum % modulo;

            // target은 (currentMod + modulo - k) % modulo
            int target = (currentMod + modulo - k) % modulo;

            // 현재까지 target이 몇 번 나왔는지 answer에 더한다
            if (countMap.find(target) != countMap.end()) {
                answer += countMap[target];
            }

            // 현재 currentMod 상태도 map에 추가
            countMap[currentMod]++;
        }

        return answer;
    }
};
