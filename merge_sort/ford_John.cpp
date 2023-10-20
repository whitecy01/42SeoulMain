// #include <iostream>
// #include <vector>
// #include <algorithm>

// struct Job {
//     char id;
//     int time;
// };

// bool compareJobs(const Job& a, const Job& b) {
//     return a.time < b.time;
// }

// void findJobSequence(std::vector<Job>& jobs) {
//     std::vector<Job> sortedJobs = jobs;
//     std::sort(sortedJobs.begin(), sortedJobs.end(), compareJobs);

//     int n = sortedJobs.size();
//     int completionTime = 0;

//     std::cout << "작업 스케줄 순서: ";
//     for (int i = 0; i < n; i++) {
//         completionTime += sortedJobs[i].time;
//         std::cout << sortedJobs[i].id << " ";

//         if (i < n - 1) {
//             std::cout << "-> ";
//         }
//     }

//     std::cout << "\n전체 완료 시간: " << completionTime << std::endl;
// }

// int main() {
//     std::vector<Job> jobs;
//     jobs.push_back({'A', 3});
//     jobs.push_back({'B', 2});
//     jobs.push_back({'C', 5});
//     jobs.push_back({'D', 4});

//     findJobSequence(jobs);

//     return 0;
// }


#include <iostream>
#include <vector>

int main() {
    // 주어진 요소들을 벡터에 저장
    std::vector<int> elements;

	elements.push_back(11);
	elements.push_back(7);
	elements.push_back(5);
	elements.push_back(3);
	elements.push_back(20);
	elements.push_back(22);

    // 결과를 저장할 벡터 생성
    std::vector<std::vector<int> > result;

    // 원래의 순서를 가지는 벡터
    std::vector<int> originalOrder(elements.begin(), elements.begin() + elements.size() / 2);
    
    // 거꾸로 된 순서를 가지는 벡터
    std::vector<int> reverseOrder(elements.rbegin(), elements.rbegin() + elements.size() / 2);
    
    // 결과 벡터에 두 벡터를 추가
    result.push_back(originalOrder);
    result.push_back(reverseOrder);
    
    // 결과 출력
    for (const std::vector<int>& vec : result) 
	{
        for (int num : vec) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
