Task: return the line number of a given string
#define fileLength 1000

char searchTerm[] = "apples"
char comparison[fileLength]

int searchTermLength = ?

int returnLineNumber(char *searchTerm, char comparison)
  if (new line)
    newLine++
  
  int offset = ? // searchTerm[i] == comparison[i - offset]

  while (searchTerm[i] == comparison[i - offset])
    if (i == searchTermLength) 
      return newLine++
    else if (i > searchTermLength)
      return -1
    i++

