
env -i: normale pipe funktioniert trotzdem wtf?
mein output:
c1r1p10% env -i ./pipex file1.txt "ls -l" "wc -l" file2.txt
command not found: ls
command not found: wc

erster cmd no access ist anders

c1r1p10% > file1.txt ./no_access | ls -l /proc/self/fd/1
zsh: permission denied: ./no_access
lrwx------ 1 slambert 2025_vienna 64 Feb  9 13:09 /proc/self/fd/1 -> /dev/pts/0
c1r1p10% 

c1r1p10% ./pipex file1.txt ./no_access "ls -l" /proc/self/fd/1
permission denied: ./no_access
total 3156
drwxr-xr-x 5 slambert 2025_vienna    4096 Feb  3 14:24  42_pipex_tester
-rwxrwxrwx 1 slambert 2025_vienna       0 Feb  4 15:12  beidl
-rw-r--r-- 1 slambert 2025_vienna       2 Feb  9 12:41  dasdsad
-rw-r--r-- 1 slambert 2025_vienna 1355877 Feb  2 11:49  en.subject.pdf
drwxr-xr-x 2 slambert 2025_vienna     116 Feb  4 15:17  fail
-rwxrwxrwx 1 slambert 2025_vienna       0 Feb  9 13:03  file1.txt
-rw-r--r-- 1 slambert 2025_vienna       0 Dec 18 12:50  file2
-rwxrwxrwx 1 slambert 2025_vienna       0 Feb  9 12:47  file2.txt
drwxr-xr-x 4 slambert 2025_vienna    4096 Feb  3 12:18  git
-rw-r--r-- 1 slambert 2025_vienna       2 Feb  9 12:39  lgkkgjkgh
drwxr-xr-x 2 slambert 2025_vienna    4096 Feb  9 13:01  libft
-rw-r--r-- 1 slambert 2025_vienna       0 Feb  4 15:03 'ls -l'
-rw-r--r-- 1 slambert 2025_vienna    1687 Feb  9 12:26  Makefile
---------- 1 slambert 2025_vienna       0 Feb  9 13:03  no_access
-rw-r--r-- 1 slambert 2025_vienna 1601006 Dec  5 14:56  OLD_en.subject.pdf
-rwxr-xr-x 1 slambert 2025_vienna   32240 Feb  9 13:01  pipex
-rw-r--r-- 1 slambert 2025_vienna    4219 Feb  3 10:27  pipex_bonus.c
-rw-r--r-- 1 slambert 2025_vienna    2497 Dec 19 14:24  pipex_bonus.h
-rw-r--r-- 1 slambert 2025_vienna    4940 Feb  9 12:57  pipex.c
-rw-r--r-- 1 slambert 2025_vienna    1950 Feb  9 12:12  pipex.h
-rw-r--r-- 1 slambert 2025_vienna    9368 Feb  9 13:01  pipex.o
drwxr-xr-x 4 slambert 2025_vienna      47 Dec 16 13:14  pipex_tester
-rw-r--r-- 1 slambert 2025_vienna    3825 Dec 19 13:58  pipex_utils1_bonus.c
-rw-r--r-- 1 slambert 2025_vienna    3696 Feb  4 17:34  pipex_utils1.c
-rw-r--r-- 1 slambert 2025_vienna    7104 Feb  9 13:01  pipex_utils1.o
-rw-r--r-- 1 slambert 2025_vienna    1770 Feb  3 11:10  pipex_utils2_bonus.c
-rw-r--r-- 1 slambert 2025_vienna    1868 Dec 19 14:10  pipex_utils2.c
-rw-r--r-- 1 slambert 2025_vienna    5392 Feb  9 13:01  pipex_utils2.o
-rw-r--r-- 1 slambert 2025_vienna    2554 Feb  3 11:29  pipex_utils3_bonus.c
-rw-r--r-- 1 slambert 2025_vienna    1409 Feb  3 12:26  README.md
-rwxr-xr-x 1 slambert 2025_vienna   62266 Dec 18 12:50 'tester_pipex (Copy).sh'
-rwxr-xr-x 1 slambert 2025_vienna   62467 Dec 18 12:50  tester_pipex.sh
c1r1p10% 

