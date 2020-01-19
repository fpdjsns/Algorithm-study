import sys
from typing import List

sys.stdin = open('resource/input.in', 'r')
sys.stdout = open('resource/output.out', 'w')


# C : test case (<= 50)
# N : 전공 과목의 수 (1 <= N <= 12)
# K : 들어야 할 과목 수 (0 <= K <= N)
# M : 학기의 수 (1 <= M <= 10)
# L : 한 학기에 최대로 들을 수 있는 과목 수 (1 <= L <= 10)

def cntBit(n):
    return n % 2 + cntBit(n // 2) if n >= 2 else n

def solve(N: int, K:int, M:int, L:int, preSubjects:List[int], semesters:List[List[int]]):
    dp = M * [[-1] * (1 << N)]
    INF = 1000000000

    # sem: 현재 학기
    # takenSubs: 수강한 과목들
    # K개의 과목을 수강하기 위해 더 다녀야 할 최소 학기
    def TPS(sem: int, takenSubs: int):

        if cntBit(takenSubs) >= K: return 0
        if sem >= M: return INF

        if dp[sem][takenSubs] != -1:
            return dp[sem][takenSubs]

        # 수강가능한 과목들 = 이번 학기에 들을 수 있는 과목들 - 이미 수강한 과목들
        willTakeSub = semesters[sem] & (~takenSubs)

        # 수강가능한 과목들에서 선수과목을 다 끝마치지 못한 과목들 제외
        for i in range(N):
            # willTakeSub에 없는 과목인 경우
            if (willTakeSub & (1 << i)) == 0: continue
            # 선수 과목을 다 들은 경우
            if (preSubjects[i] & takenSubs) == preSubjects[i]: continue
            # i 번째 과목 삭제
            willTakeSub &= ~(1<<i)

        ans = INF

        # 수강가능한 과목들을 탐색하면서 해당 과목을 수강하였을 때 다녀야 하는 최소 학기 구하기
        # willTakeSub의 모든 부분 집합
        take = willTakeSub
        while take > 0:
            # L개 이상의 과목은 한 학기에 들을 수 없다.
            if (cntBit(take)) > L: continue
            ans = min(ans, TPS(sem+1, takenSubs | take) + 1)
            take = ((take - 1) & willTakeSub)

        # 현재 학기에 아무것도 수강하지 않은 경우
        ans = min(ans, TPS(sem + 1, takenSubs))

        dp[sem][takenSubs] = ans
        return ans
    ans = TPS(0, 0)
    return ans if ans < INF else "IMPOSSIBLE"

# main
C = int(input())
for i in range(C):
    N, K, M, L = map(int, sys.stdin.readline().split(' '))

    # N개의 과목 정보(선수 과목의 수, 선수 과목 번호들)
    preSubjects = [0] * N
    for i in range(N):
        tmpPreSubs = list(map(int, sys.stdin.readline().split(' ')))
        cnt = tmpPreSubs[0]
        tmpPreSubs = tmpPreSubs[1:cnt+1]
        for preSub in tmpPreSubs:
            preSubjects[i] |= (1 << preSub)

    # M개의 학기 정보(개설 과목 수, 개설되는 과목 번호들)
    semesters = [0] * M
    for i in range(M):
        tmpSems = list(map(int, sys.stdin.readline().split(' ')))
        cnt = tmpSems[0]
        tmpSems = tmpSems[1:cnt+1]
        for tmpSem in tmpSems:
            semesters[i] |= (1 << tmpSem)

    print(solve(N, K, M, L, preSubjects, semesters))
