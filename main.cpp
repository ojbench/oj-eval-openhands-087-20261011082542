#include <iostream>
#include <vector>
using namespace std;

// Function to find the final position of the nth ball (last switch it passes through)
int findFinalPosition(int D, long long n) {
    int position = 1;  // Start at root
    
    for (int level = 0; level < D - 1; level++) {
        // At each switch, determine if the nth ball goes left or right
        // If the nth ball is odd-numbered at this switch, it goes left
        // If it's even-numbered, it goes right
        
        if (n % 2 == 1) {
            // Odd-numbered ball goes left
            position = position * 2;
            n = (n + 1) / 2;  // Ball number in left subtree
        } else {
            // Even-numbered ball goes right
            position = position * 2 + 1;
            n = n / 2;  // Ball number in right subtree
        }
    }
    
    return position;
}

// Function to compute the state of all switches at the bottom level
vector<int> computeBottomSwitchStates(int D, long long n) {
    vector<int> states(1 << (D - 1), 0);
    
    // For each switch at the bottom level, compute how many balls pass through it
    for (int switch_idx = 0; switch_idx < (1 << (D - 1)); switch_idx++) {
        long long balls_through = n;
        int current_pos = 1;
        
        // Navigate from root to the target switch
        for (int level = 0; level < D - 1; level++) {
            long long left_balls = (balls_through + 1) / 2;
            long long right_balls = balls_through / 2;
            
            // Determine which child contains our target switch
            int bit_at_level = (switch_idx >> ((D - 2) - level)) & 1;
            
            if (bit_at_level == 0) {
                // Target switch is in left subtree
                balls_through = left_balls;
                current_pos = current_pos * 2;
            } else {
                // Target switch is in right subtree
                balls_through = right_balls;
                current_pos = current_pos * 2 + 1;
            }
            
            if (balls_through == 0) break;
        }
        
        states[switch_idx] = balls_through % 2;
    }
    
    return states;
}

int main() {
    int D;
    long long n;
    cin >> D >> n;
    
    // Find final position of the nth ball
    int final_position = findFinalPosition(D, n);
    
    // Compute states of switches at the bottom level
    vector<int> switch_states = computeBottomSwitchStates(D, n);
    
    // Output final position
    cout << final_position << endl;
    
    // Output switch states
    for (int i = 0; i < switch_states.size(); i++) {
        if (i > 0) cout << " ";
        cout << switch_states[i];
    }
    cout << endl;
    
    return 0;
}