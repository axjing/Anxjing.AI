'''
@Author: Anxjing.AI
@Date: 2020-06-08 19:08:13
@LastEditTime: 2020-06-08 19:10:41
@LastEditors: Anajing.AI
@Description: 
@FilePath: \Anxjing.AI\algorithm_note\getOffer\leet最长覆盖子串.py
@THIS FILE IS PART OF Anxjing.AI PROJECT
'''
class Solution():
    def minWindow(self, s: 'str', t: 'str') -> 'str':
            from collections import Counter
            t = Counter(t)
            lookup = Counter()
            start = 0
            end = 0
            min_len = float("inf")
            res = ""
            while end < len(s):
                lookup[s[end]] += 1
                end += 1
                #print(start, end)
                while all(map(lambda x: lookup[x] >= t[x], t.keys())):
                    if end - start < min_len:
                        res = s[start:end]
                        min_len = end - start
                    lookup[s[start]] -= 1
                    start += 1
            return res

S="LMNLEKJLAFLFJKJMFEEFX"

T="EFJ"
Sol = Solution()
res = Sol.minWindow(S, T)
print(res)