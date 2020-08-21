void rotate(char matrix[10][10]) {
  int rng = 9;
  for(int i = 0; i < 5; i++) {
    for(int j = i; j < 9 - i; j++) {
      char temp = matrix[i][j];
      matrix[i][j] = matrix[rng - j][i];
      matrix[rng - j][i] = matrix[rng - i][rng - j];
      matrix[rng - i][rng - j] = matrix[j][rng - i];
      matrix[j][rng - i] = temp;
    }
  }
}
