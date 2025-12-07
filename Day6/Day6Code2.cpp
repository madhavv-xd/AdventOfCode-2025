#include <bits/stdc++.h>
using namespace std;

// This solution works, unoptimised and messed up shi

int main()
{
   string line;
   ifstream file("input.txt");
   long long result = 0;

   vector<string> lines;

   // Read the entire file line by line and store it.
   // The puzzle input is formatted in a specific vertical layout,
   // so we can’t parse it in a normal left-to-right style.
   while (getline (file, line)) {
      lines.push_back(line);
   }
   file.close();

   // The last line contains only the operators (* or +).
   // Everything above it contains digits stacked vertically.
   string symbolLine = lines[lines.size()-1];
   lines.erase(lines.begin() + lines.size()-1);

   // We will build two things:
   // 1) symbols  -> holds the operators in order (*, +, *, ...)
   // 2) sizes    -> how many columns belong to each operator block
   vector<int> sizes;
   vector<char> symbols;
   int size = 0;

   // This loop scans the operator line and figures out how big each "block"
   // of numbers is. The input visually groups numbers under spaces,
   // so we count those spaces until we hit another operator.
   for(int i = 0; i < symbolLine.length(); i++)
   {
      // If we're on the LAST character of the string,
      // we push the accumulated size (final group)
      if(i == symbolLine.length() - 1)
         sizes.push_back(++size);

      // If the current character is an operator (* or +),
      // that means a new block starts here.
      else if(symbolLine[i] == '*' || symbolLine[i] == '+' )
      {         
         symbols.push_back(symbolLine[i]); // Record this operator

         // If size is still zero, it means we're at the FIRST operator,
         // so there’s no "previous block" to push yet.
         if(size == 0)
         {
            size = 1;
            continue;
         }

         // Otherwise, we just finished counting a block → store it.
         sizes.push_back(--size);

         // Reset size for the next block (starting count from 1 again).
         size = 1;
      }
      else 
         // Just a space — part of a block, so count it.
         size++;
   }

   // We'll now walk column-by-column according to the sizes[] values.
   // Each column represents a vertically stacked number.
   int pos = 0;

   for(int i = 0; i < symbols.size(); i++)
   {
      long long sum;

      // Initialize based on operation type
      // Multiply starts at 1, addition starts at 0.
      if(symbols[i] == '*') sum = 1;
      else sum = 0;

      // For each column belonging to this operator block...
      for(int j = 0; j < sizes[i]; j++)
      {
         string num = "";

         // Build a vertical number by reading characters DOWN the grid.
         for(int k = 0; k < lines.size(); k++)
         {
            char c = lines[k][pos];
            if(c == ' ') continue; // ignore empty filler spaces
            num += c;
         }

         // Apply the operator to this number
        if(symbols[i] == '*') sum *= stoi(num);
         else sum += stoi(num);

         pos++; // move to the next column
      }

      // Skip the visual separator column (the space between column groups)
      pos++;

      result += sum; // Add this block’s result to the final answer
   }

   // Done!
   cout << "The answer is: " << result << endl;
}
