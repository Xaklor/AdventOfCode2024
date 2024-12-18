#include <iostream>
#include <string.h>
using namespace std;

void simulate(long, long[], long[]);
long search(long, long[]);
long ctol(long[]);
long otoi(long, long, long, long);
long input[] = { 2,4,1,5,7,5,1,6,0,3,4,2,5,5,3,0 };

int main() {
    // part 1
    long output[16]; memset(output, -1, sizeof(output));
    simulate(44348299, input, output);
    for(long i: output) 
        cout << i << ',';
    cout << endl;

    // part 2
    long chunks[16]; memset(chunks, 0, sizeof(chunks));
    cout << search(0, chunks) << endl;
}

long search(long chunk_idx, long prev_chunks[]) {
    if(chunk_idx == 16)
        return ctol(prev_chunks);

    long result = 1l << 48;
    for(long n = 0; n < 8; n++) {
        prev_chunks[chunk_idx] = n;
        long output[16]; memset(output, -1, sizeof(output));
        simulate(ctol(prev_chunks), input, output);
        bool valid = true;
        for(long i = 0; i <= chunk_idx; i++) {
            if(output[15 - i] != input[15 - i]) {
                valid = false;
            }
        }
        if(valid)
            result = min(result, search(chunk_idx + 1, prev_chunks));
    }
    return result;
}

void simulate(long init, long program[], long output[]) {
    long A = init;
    long B = 0;
    long C = 0;
    long pointer = 0;
    long out = 0;
    while(pointer < 15) {
        switch(program[pointer]) {
            // adv instruction: perform A / 2^(combo op), write to A
            case 0: A = A >> otoi(program[pointer + 1], A, B, C); break;
            // bxl instruction: perform B XOR (literal op), write to B
            case 1: B = B ^ program[pointer + 1]; break;
            // bst instruction: perform (combo op) % 8, write to B
            case 2: B = otoi(program[pointer + 1], A, B, C) % 8; break;
            // jnz instruction: if A is not 0, pointer = (literal op), decrement pointer to counteract the increment
            case 3: if(A != 0) pointer = program[pointer + 1] - 2; break;
            // bxc instruction: perform B XOR C, write to B
            case 4: B = B ^ C; break;
            // out instruction: output (combo op) % 8
            case 5: output[out] = otoi(program[pointer + 1], A, B, C) % 8; out++; break;
            // bdv instruction: perform A / 2^(combo op), write to B
            case 6: B = A >> otoi(program[pointer + 1], A, B, C); break;
            // cdv instruction: perform A / 2^(combo op), write to C
            case 7: C = A >> otoi(program[pointer + 1], A, B, C); break;
        }
        pointer += 2;
    }
}

// converts opcode to long
long otoi(long op, long A, long B, long C) {
    if(op <= 3) return op;
    if(op == 4) return A;
    if(op == 5) return B;
    if(op == 6) return C;
    return 0;
}

// converts chunk array to long
long ctol(long chunks[]) {
    long result = chunks[0];
    for(long i = 1; i < 16; i++) {
        result = (result << 3) + chunks[i];
    }
    return result;
}