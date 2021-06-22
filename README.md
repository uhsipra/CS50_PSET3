# CS50_PSET3
For plurality background information
From the CS50x website: Elections come in all shapes and sizes. 
In the UK, the Prime Minister is officially appointed by the monarch, who generally chooses the leader of the political party that wins the most seats in the House of Commons. 
The United States uses a multi-step Electoral College process where citizens vote on how each state should allocate Electors who then elect the President.
Perhaps the simplest way to hold an election, though, is via a method commonly known as the “plurality vote” (also known as “first-past-the-post” or “winner take all”). 
In the plurality vote, every voter gets to vote for one candidate. 
At the end of the election, whichever candidate has the greatest number of votes is declared the winner of the election.

Specifications for plurality:
1. The "vote" function takes a single argument, a string called name, representing the name of the candidate who was voted for.
If name matches one of the names of the candidates in the election, then update that candidate’s vote total to account for the new vote. The vote function in this case should return true to indicate a successful ballot.
If name does not match the name of any of the candidates in the election, no vote totals should change, and the vote function should return false to indicate an invalid ballot.
You may assume that no two candidates will have the same name.
2. The "print_winner" function should print out the name of the candidate who received the most votes in the election, and then print a newline.
It is possible that the election could end in a tie if multiple candidates each have the maximum number of votes. In that case, you should output the names of each of the winning candidates, each on a separate line.

For Runoff background information
From CS50x website: One ranked choice voting system is the instant runoff system. In an instant runoff election, voters can rank as many candidates as they wish. 
If any candidate has a majority (more than 50%) of the first preference votes, that candidate is declared the winner of the election.
If no candidate has more than 50% of the vote, then an “instant runoff” occurrs. The candidate who received the fewest number of votes is eliminated from the election, 
and anyone who originally chose that candidate as their first preference now has their second preference considered. Why do it this way? 
Effectively, this simulates what would have happened if the least popular candidate had not been in the election to begin with.
The process repeats: if no candidate has a majority of the votes, the last place candidate is eliminated, 
and anyone who voted for them will instead vote for their next preference (who hasn’t themselves already been eliminated). 
Once a candidate has a majority, that candidate is declared the winner.

Specifications for Runoff:
1. Complete the vote function.

The function takes arguments voter, rank, and name. If name is a match for the name of a valid candidate, then you should update the global preferences array to indicate that the voter voter has that candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.).
If the preference is successfully recorded, the function should return true; the function should return false otherwise (if, for instance, name is not the name of one of the candidates).
You may assume that no two candidates will have the same name.

2. Complete the tabulate function.

The function should update the number of votes each candidate has at this stage in the runoff.
Recall that at each stage in the runoff, every voter effectively votes for their top-preferred candidate who has not already been eliminated.

3. Complete the print_winner function.

If any candidate has more than half of the vote, their name should be printed to stdout and the function should return true.
If nobody has won the election yet, the function should return false.

4. Complete the find_min function.

The function should return the minimum vote total for any candidate who is still in the election.

5. Complete the is_tie function.

The function takes an argument min, which will be the minimum number of votes that anyone in the election currently has.
The function should return true if every candidate remaining in the election has the same number of votes, and should return false otherwise.

6. Complete the eliminate function.

The function takes an argument min, which will be the minimum number of votes that anyone in the election currently has.
The function should eliminate the candidate (or candidates) who have min number of votes.
