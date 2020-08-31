# INC 2018 - Problem Repository

## Repository Structure

Each problem (from A to M) has their own folder. The folder name is the `slug` of the problem, which is the codename we used when we internally prepare the problems. The following table describes the slug for each problem

| Problem Code | Problem Slug | Problem Title                       |
| ------------ | ------------ | ----------------------------------- |
| A            | binus        | Tour de BINUS                       |
| B            | link         | Linked List                         |
| C            | hierarchy    | Hierarchy Structure                 |
| D            | permutation  | Substring Permutation               |
| E            | superb       | The Good, the Great, and the Superb |
| F            | kmp          | KMP                                 |
| G            | discs        | Discs                               |
| H            | plate        | Plate Parity                        |
| I            | expected     | Expected Value of a Permutation     |
| J            | groups       | A Study on Groups                   |
| K            | living       | Living Subgraph                     |
| L            | tournament   | Fair Tournament                     |
| M            | move         | Moving Around                       |

In the problem folder, there should be at least the following file/folder:

- `solution.cpp`. The official solution used to generate the outputs of the testcases
- `verifier.cpp`. A verifier used to validate the input of the testcases. The code will crash if the input violates the problem constraint, while it will exit gracefully and will not output anything if the input satisfies the problem constraint.
- `tc/`. A folder consisting of all testcases. The sample inputs given in the problem statement will be in the form of `<slug>_sample_<testcase number>.in/out`, while the hidden testcases will be in the form of `<slug>_1_<testcase number>.in/out`.
- `p-<slug>.pdf`. The problem statement distributed to the contestants during the contest.

For the problem with multiple correct outputs for each input, there should be one more file in the problem folder:

- `scorer.cpp`. The code accepts three arguments.
  - The first parameter will be used as the filename of the input file
  - The second parameter will be used as the filename of the judge's output file
  - The third parameter will be used as the filename of the contestant's output file
  - This code will print `WA` to stdout if the contestant's output is intended to be judged `WRONG ANSWER`, while it will print `AC` to stdout if the contestants's output is intended to be judged `CORRECT`.

## Limitations

The following table describes the time limit for each problem, as broadcasted to all teams at the beginning of the contest:

| Problem Code | Problem Slug | Time Limit |
| ------------ | ------------ | ---------- |
| A            | binus        | 1 sec      |
| B            | link         | 1 sec      |
| C            | hierarchy    | 3 sec      |
| D            | permutation  | 1 sec      |
| E            | superb       | 1 sec      |
| F            | kmp          | 1 sec      |
| G            | discs        | 1 sec      |
| H            | plate        | 1 sec      |
| I            | expected     | 1 sec      |
| J            | groups       | 1 sec      |
| K            | living       | 1 sec      |
| L            | tournament   | 2 sec      |
| M            | move         | 1 sec      |

The memory limit for all problems is 256MB, as announced in the technical briefing of the contest.

## Solutions

Note that while there is only one official published solution, we have a lot of other solutions prepared for our internal testing. These other solutions include, but not limited to:

- Solutions in several other languages
- Solutions that is intended to be incorrect (e.g. WA, TLE, etc.)
- Other correct solutions (especially on problems with more than one correct outputs for each input)

## Errata

Note that the following announcement was broadcasted to all teams during the contest:

- Problem I: A Study on Groups
  
```	
There is a typo in the problem statement of this problem. The word "incides"
should be "indices". The problem statement is now fixed (both in the individual
and in the complete problem set), please refresh the problem statement.
```

- Problem F:KMP
  
```	
There is also a typo in the problem statement of this problem. Algorithm name
"PKD" is actually not valid in the example. We intent to write "PKH" instead.

Also, we added a clarification that "the algorithm can be named by taking
exactly one of those first characters from each name *(in the subset of the N
computer scientists)*".

The problem statement is now fixed (both in the individual and in the complete
problem set), please refresh the problem statement.
```

For both problems, the soft copy of the problem statements provided in this repository are the ones distributed after the fix was made.
