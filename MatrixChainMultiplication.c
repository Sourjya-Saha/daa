#include <stdio.h>
#include <limits.h>

// Function to print optimal parenthesization
void printOptimalParens(int s[][10], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Function to compute minimum scalar multiplications
int MatrixChainOrder(int p[], int n) {
    int m[10][10]; // Minimum scalar multiplications
    int s[10][10]; // Optimal split position

    int i, j, k, L, q;

    // Initialize the diagonal to 0: cost of multiplying one matrix is 0
    for (i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // L is the chain length (from 2 to n)
    for (L = 2; L < n; L++) {
        for (i = 1; i < n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = INT_MAX;

            for (k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1]*p[k]*p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nOptimal Parenthesization is: ");
    printOptimalParens(s, 1, n - 1);
    printf("\n");

    return m[1][n - 1];
}

int main() {
    int n, i;
    int p[10]; // Dimensions array

    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    printf("Enter the dimensions (in order):\n");
    for (i = 0; i <= n; i++) {
        printf("p[%d] = ", i);
        scanf("%d", &p[i]);
    }

    int minMultiplications = MatrixChainOrder(p, n + 1);
    printf("Minimum number of scalar multiplications is: %d\n", minMultiplications);

    return 0;
}
