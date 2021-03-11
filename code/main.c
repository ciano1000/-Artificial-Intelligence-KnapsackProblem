#define _CRT_RAND_S
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "utils.h"

#define N 1000
#define SIZE 20
#define ITERATIONS 20
#define MUTATION_RATE 1
#define K 7

#define ASCII_TO_DECIMAL(c) (c - 48)
#define DECIMAL_TO_ASCII(d) (d + 48)

void part_ai(void);
void part_aii(char *target, u32 size);
void part_aiii(u32 num_initial_all_zero);

void knapsack(u32 knapsack_size);

int main(void) {
    
    //part_ai();
    //part_aii("11001101110011001111", SIZE);
    //part_aiii(50);
    //knapsack(103);
    knapsack(156);
}

void part_ai(void) {
    f32 average_fitness[ITERATIONS];
    
    char population[N][SIZE + 1]; //1 extra for the null terminator
    char mating_pool[N][SIZE + 1]; 
    
    u32 population_fitness[N];
    
    //generate our populations intial state and fitness
    for(u32 i = 0; i < N; i++) {
        u32 fitness = 0;
        
        for(u32 j = 0; j < SIZE; j++) {
            u32 rand = 0;
            rand_s(&rand);
            rand = rand % 2;
            fitness += (rand == 1) ? 1:0;
            population[i][j] = DECIMAL_TO_ASCII((char)rand);
        }
        population[i][SIZE] = null;
        population_fitness[i] = fitness;
        //printf("%s\t%d\n", population[i], fitness);
    }
    
    u32 generation = 0;
    while(generation < ITERATIONS) {
        //Tournament Selection
        for(u32 i = 0; i < N; i++) {
            u32 max_fitness_idx = 0;
            u32 max_fitness = 0;
            for(u32 j = 0; j < K; j++) {
                u32 idx = 0;
                rand_s(&idx);
                idx = idx % N;
                
                if(population_fitness[idx] > max_fitness) {
                    max_fitness = population_fitness[idx];
                    max_fitness_idx = idx;
                }
            }
            strcpy(mating_pool[i], population[max_fitness_idx]);
        }
        
        
        u32 sum_fitness = 0;
        u32 max_fitness = 0;
        for(u32 i = 0; i < N; i++) {
            u32 idx_1 = 0;
            u32 idx_2 = 0;
            
            rand_s(&idx_1);
            rand_s(&idx_2);
            
            idx_1 = idx_1 % N;
            idx_2 = idx_2 % N;
            
            char *parent_1 = mating_pool[idx_1];
            char *parent_2 = mating_pool[idx_2];
            
            //Perform crossover and mutation
            u32 midpoint = 0;
            rand_s(&midpoint);
            midpoint = midpoint % SIZE;
            midpoint += (midpoint == 0) ? 1:0;
            
            u32 child_fitness = 0;
            
            char child_buffer[SIZE + 1];
            for(u32 j = 0; j < midpoint; j++) {
                u32 rand = 0;
                rand_s(&rand);
                rand = (rand % 100);
                
                u32 modifier = 0;
                
                if(rand <= MUTATION_RATE) {
                    if(ASCII_TO_DECIMAL(parent_1[j]) == 0)
                        modifier = 1;
                    else
                        modifier = -1;
                }
                
                child_buffer[j] = parent_1[j] + modifier;
                child_fitness += ASCII_TO_DECIMAL(child_buffer[j]);
            }
            
            for(u32 j = midpoint; j < SIZE; j++) {
                u32 rand = 0;
                rand_s(&rand);
                rand = (rand % 100);
                
                u32 modifier = 0;
                
                if(rand <= MUTATION_RATE) {
                    if(ASCII_TO_DECIMAL(parent_2[j]) == 0)
                        modifier = 1;
                    else
                        modifier = -1;
                }
                
                child_buffer[j] = parent_2[j] + modifier;
                child_fitness += ASCII_TO_DECIMAL(child_buffer[j]);
            }
            child_buffer[SIZE] = null;
            
            strcpy(population[i], child_buffer);
            population_fitness[i] = child_fitness;
            sum_fitness += child_fitness;
            if(population_fitness[i] > max_fitness) {
                max_fitness = population_fitness[i];
            }
        }
        
        average_fitness[generation] = (f32)sum_fitness / (f32)N;
        //printf("Generation: %d Best Fitness: %d Avg Fitness: %.2f \n", generation, max_fitness, average_fitness[generation]); 
        printf("%d,%d,%.2f\n", generation, max_fitness, average_fitness[generation]); 
        generation++;
    }
}

u32 target_fitness_calc(char *target, char* actual, u32 size) {
    u32 fitness = 0;
    
    for(u32 i = 0; i < size; i++) {
        if(target[i] == actual[i])
            fitness++;
    }
    
    return fitness;
}

void part_aii(char *target, u32 size) {
    f32 average_fitness[ITERATIONS];
    
    char population[N][SIZE + 1]; //1 extra for the null terminator
    char mating_pool[N][SIZE + 1]; 
    
    u32 population_fitness[N];
    
    //generate our populations intial state and fitness
    for(u32 i = 0; i < N; i++) {
        for(u32 j = 0; j < SIZE; j++) {
            u32 rand = 0;
            rand_s(&rand);
            rand = rand % 2;
            population[i][j] = DECIMAL_TO_ASCII((char)rand);
        }
        population[i][SIZE] = null;
        population_fitness[i] = target_fitness_calc(target, population[i], size);
        //printf("%s\t%d\n", population[i], fitness);
    }
    
    u32 generation = 0;
    while(generation < ITERATIONS) {
        //Tournament Selection
        for(u32 i = 0; i < N; i++) {
            u32 max_fitness_idx = 0;
            u32 max_fitness = 0;
            for(u32 j = 0; j < K; j++) {
                u32 idx = 0;
                rand_s(&idx);
                idx = idx % N;
                
                if(population_fitness[idx] > max_fitness) {
                    max_fitness = population_fitness[idx];
                    max_fitness_idx = idx;
                }
            }
            strcpy(mating_pool[i], population[max_fitness_idx]);
        }
        
        
        u32 sum_fitness = 0;
        u32 max_fitness = 0;
        for(u32 i = 0; i < N; i++) {
            u32 idx_1 = 0;
            u32 idx_2 = 0;
            
            rand_s(&idx_1);
            rand_s(&idx_2);
            
            idx_1 = idx_1 % N;
            idx_2 = idx_2 % N;
            
            char *parent_1 = mating_pool[idx_1];
            char *parent_2 = mating_pool[idx_2];
            
            //Perform crossover and mutation
            u32 midpoint = 0;
            rand_s(&midpoint);
            midpoint = midpoint % SIZE;
            midpoint += (midpoint == 0) ? 1:0;
            
            char child_buffer[SIZE + 1];
            for(u32 j = 0; j < midpoint; j++) {
                u32 rand = 0;
                rand_s(&rand);
                rand = (rand % 100);
                
                u32 modifier = 0;
                
                if(rand <= MUTATION_RATE) {
                    if(ASCII_TO_DECIMAL(parent_1[j]) == 0)
                        modifier = 1;
                    else
                        modifier = -1;
                }
                
                child_buffer[j] = parent_1[j] + modifier;
            }
            
            for(u32 j = midpoint; j < SIZE; j++) {
                u32 rand = 0;
                rand_s(&rand);
                rand = (rand % 100);
                
                u32 modifier = 0;
                
                if(rand <= MUTATION_RATE) {
                    if(ASCII_TO_DECIMAL(parent_2[j]) == 0)
                        modifier = 1;
                    else
                        modifier = -1;
                }
                
                child_buffer[j] = parent_2[j] + modifier;
            }
            child_buffer[SIZE] = null;
            
            strcpy(population[i], child_buffer);
            population_fitness[i] = target_fitness_calc(target, population[i], size);
            sum_fitness += population_fitness[i];
            if(population_fitness[i] > max_fitness) {
                max_fitness = population_fitness[i];
            }
            
        }
        
        average_fitness[generation] = (f32)sum_fitness / (f32)N;
        //printf("Generation: %d Best Fitness: %d Avg Fitness: %.2f \n", generation, max_fitness, average_fitness[generation]); 
        printf("%d,%d,%.2f\n", generation, max_fitness, average_fitness[generation]); 
        generation++;
    }
}

u32 deceptive_landscape_fitness(char *current_genome) {
    u32 fitness = 0;
    
    for(u32 i = 0; i < SIZE; i++) {
        fitness +=  ASCII_TO_DECIMAL(current_genome[i]);
    }
    
    //no 0's
    if(fitness == 0)
        fitness = SIZE * 2;
    
    return fitness;
}

void part_aiii(u32 num_initial_all_zero) {
    u32 mod_value = N / num_initial_all_zero;
    
    f32 average_fitness[ITERATIONS];
    
    char population[N][SIZE + 1]; //1 extra for the null terminator
    char mating_pool[N][SIZE + 1]; 
    
    u32 population_fitness[N];
    
    //generate our populations intial state and fitness - to test the deceptive landscape, I will place 10 all 0 entries in the population
    for(u32 i = 0; i < N; i++) {
        
        if((i % mod_value) == 0) {
            strcpy(population[i], "00000000000000000000");
        } else {
            for(u32 j = 0; j < SIZE; j++) {
                u32 rand = 0;
                rand_s(&rand);
                rand = rand % 2;
                population[i][j] = DECIMAL_TO_ASCII((char)rand);
            }
        }
        population[i][SIZE] = null;
        population_fitness[i] = deceptive_landscape_fitness(population[i]);
        //printf("%s\t%d\n", population[i], fitness);
    }
    
    u32 generation = 0;
    while(generation < ITERATIONS) {
        //Tournament Selection
        for(u32 i = 0; i < N; i++) {
            u32 max_fitness_idx = 0;
            u32 max_fitness = 0;
            for(u32 j = 0; j < K; j++) {
                u32 idx = 0;
                rand_s(&idx);
                idx = idx % N;
                
                if(population_fitness[idx] > max_fitness) {
                    max_fitness = population_fitness[idx];
                    max_fitness_idx = idx;
                }
            }
            strcpy(mating_pool[i], population[max_fitness_idx]);
        }
        
        
        u32 sum_fitness = 0;
        u32 max_fitness = 0;
        for(u32 i = 0; i < N; i++) {
            u32 idx_1 = 0;
            u32 idx_2 = 0;
            
            rand_s(&idx_1);
            rand_s(&idx_2);
            
            idx_1 = idx_1 % N;
            idx_2 = idx_2 % N;
            
            char *parent_1 = mating_pool[idx_1];
            char *parent_2 = mating_pool[idx_2];
            
            //Perform crossover and mutation
            u32 midpoint = 0;
            rand_s(&midpoint);
            midpoint = midpoint % SIZE;
            midpoint += (midpoint == 0) ? 1:0;
            
            char child_buffer[SIZE + 1];
            for(u32 j = 0; j < midpoint; j++) {
                u32 rand = 0;
                rand_s(&rand);
                rand = (rand % 100);
                
                u32 modifier = 0;
                
                if(rand <= MUTATION_RATE) {
                    if(ASCII_TO_DECIMAL(parent_1[j]) == 0)
                        modifier = 1;
                    else
                        modifier = -1;
                }
                
                child_buffer[j] = parent_1[j] + modifier;
            }
            
            for(u32 j = midpoint; j < SIZE; j++) {
                u32 rand = 0;
                rand_s(&rand);
                rand = (rand % 100);
                
                u32 modifier = 0;
                
                if(rand <= MUTATION_RATE) {
                    if(ASCII_TO_DECIMAL(parent_2[j]) == 0)
                        modifier = 1;
                    else
                        modifier = -1;
                }
                
                child_buffer[j] = parent_2[j] + modifier;
            }
            child_buffer[SIZE] = null;
            
            strcpy(population[i], child_buffer);
            population_fitness[i] = deceptive_landscape_fitness(population[i]);
            sum_fitness += population_fitness[i];
            if(population_fitness[i] > max_fitness) {
                max_fitness = population_fitness[i];
            }
            
        }
        
        average_fitness[generation] = (f32)sum_fitness / (f32)N;
        //printf("Generation: %d Best Fitness: %d Avg Fitness: %.2f \n", generation, max_fitness, average_fitness[generation]); 
        printf("%d,%d,%.2f\n", generation, max_fitness, average_fitness[generation]); 
        generation++;
    }
}

u32 knapsack_fitness(u32 *values, u32 *weights, u32 *indices, u32 num_items, u32 knapsack_size) {
    u32 value_sum = 0;
    u32 weight_sum = 0;
    
    for (u32 i = 0; i < num_items; i += 1){
        u32 item_idx = indices[i];
        
        value_sum += values[item_idx];
        weight_sum += weights[item_idx];
    }
    
    return (weight_sum <= knapsack_size) ? value_sum : 0; 
}

//function to prevent duplicate items in a solution
b32 naive_item_already_exists(u32 *solution_indices, u32 item_count, u32 new_index) {
    b32 result = false;
    
    for (u32 i = 0; i < item_count; i += 1){
        if(solution_indices[i] == new_index){
            result = true;
            break;
        }
    }
    
    return result;
}

void knapsack(u32 knapsack_size) {
    // Representation: candidate solutions are represented as an array of indices into the weight/value vectors and a size indicating how many items are used
    //The fitness function is equal to the sum of the values while the sum of the weights is less than the threshold of the knapsack
    
#define NUM_ITEMS 10
    
    u32 values[] = {78, 35, 89, 36, 94, 75, 74, 79, 80, 16};
    u32 weights[] = {18, 9, 23, 20, 59, 61, 70, 75, 76, 30};
    
    u32 solutions_indices[N][NUM_ITEMS];
    u32 solutions_item_counts[N];
    u32 solutions_fitnesses[N];
    
    u32 mating_pool[N];
    
    //Init our population with random items and random number of items
    for (u32 i = 0; i < N; i += 1){
        u32 num_items = 1;
        rand_s(&num_items);
        num_items = (num_items % NUM_ITEMS) + 1;
        
        solutions_item_counts[i] = num_items;
        
        for (u32 j = 0; j < num_items; j += 1){
            u32 rand_item = 0;
            do {
                rand_s(&rand_item);
                rand_item = rand_item % NUM_ITEMS;
            } while(naive_item_already_exists(solutions_indices[i], j, rand_item));
            solutions_indices[i][j] = rand_item;
        }
        
        solutions_fitnesses[i] = knapsack_fitness(values, weights, solutions_indices[i], num_items, knapsack_size);
        //printf("Fitness: %d \n", solutions_fitnesses[i]); 
    }
    
    
    u32 generation = 0;
    while(generation < ITERATIONS) {
        //Tournament Selection
        for(u32 i = 0; i < N; i++) {
            u32 max_fitness_idx = 0;
            u32 max_fitness = 0;
            for(u32 j = 0; j < K; j++) {
                u32 idx = 0;
                rand_s(&idx);
                idx = idx % N;
                
                if(solutions_fitnesses[idx] > max_fitness) {
                    max_fitness = solutions_fitnesses[idx];
                    max_fitness_idx = idx;
                }
            }
            mating_pool[i] = max_fitness_idx;
        }
        
        
        u32 sum_fitness = 0;
        u32 max_fitness = 0;
        for(u32 i = 0; i < N; i++) {
            u32 idx_1 = 0;
            u32 idx_2 = 0;
            
            rand_s(&idx_1);
            rand_s(&idx_2);
            
            idx_1 = idx_1 % N;
            idx_2 = idx_2 % N;
            
            u32 parent_1_idx = mating_pool[idx_1];
            u32 parent_2_idx = mating_pool[idx_2];
            
            u32 parent_1_count = solutions_item_counts[parent_1_idx];
            u32 parent_2_count = solutions_item_counts[parent_2_idx];
            
            u32 parent_max_count = parent_2_count;
            //ensure smallest parent is first
            if(parent_1_count > parent_2_count) {
                u32 temp = parent_1_count;
                u32 temp_idx = parent_1_idx;
                
                parent_1_count = parent_2_count;
                parent_2_count = temp;
                
                parent_1_idx = parent_2_idx;
                parent_2_idx = temp_idx;
                
                parent_max_count = temp;
            }
            
            //Perform crossover and mutation
            u32 midpoint = 0;
            rand_s(&midpoint);
            midpoint = midpoint % parent_max_count;
            midpoint += (midpoint == 0) ? 1:0;
            midpoint = (midpoint > parent_1_count) ? parent_1_count : midpoint;
            
            solutions_item_counts[i] = parent_max_count;
            for(u32 j = 0; j < parent_max_count; j++) {
                u32 *items_array = solutions_indices[parent_1_idx];
                if(j >= midpoint)
                    items_array = solutions_indices[parent_2_idx];
                
                //bit of a hack, and a bit brute-force: if current crossover item already exists, then pick the first item that doesn't exist from the current parent,
                //if we still haven't found a unique item try the other parent, if we still haven't found a unique item 
                if(naive_item_already_exists(solutions_indices[i], j, items_array[j])) {
                    //This is horrible code but it's fine for this
                    u32 rand_item = 0;
                    for(u32 i = 0; i < parent_1_count; i++) {
                        rand_s(&rand_item);
                        rand_item = rand_item % NUM_ITEMS;
                        if(!naive_item_already_exists(solutions_indices[i], j, rand_item)) 
                            break;
                    }
                    
                    if(naive_item_already_exists(solutions_indices[i], j, rand_item)) {
                        for(u32 i = 0; i < parent_2_count; i++) {
                            rand_s(&rand_item);
                            rand_item = rand_item % NUM_ITEMS;
                            if(!naive_item_already_exists(solutions_indices[i], j, rand_item)) 
                                break;
                        }
                    }
                    
                    if(naive_item_already_exists(solutions_indices[i], j, rand_item)) {
                        for(u32 i = 0; i < NUM_ITEMS; i++) {
                            rand_s(&rand_item);
                            rand_item = rand_item % NUM_ITEMS;
                            if(!naive_item_already_exists(solutions_indices[i], j, rand_item)) 
                                break;
                        }
                    }
                }
                
                
                solutions_indices[i][j] = items_array[j];
                
                u32 rand = 0;
                rand_s(&rand);
                rand = (rand % 100);
                
                if(rand <= MUTATION_RATE && parent_max_count != NUM_ITEMS) {
                    //pick a new random item and replace the current one
                    u32 rand_item = 0;
                    do {
                        rand_s(&rand_item);
                        rand_item = rand_item % NUM_ITEMS;
                    } while(naive_item_already_exists(solutions_indices[i], j, rand_item));
                    
                    solutions_indices[i][j] = rand_item;
                }
                
            }
            solutions_fitnesses[i] = knapsack_fitness(values, weights, solutions_indices[i], parent_max_count, knapsack_size);
            
            sum_fitness += solutions_fitnesses[i];
            if(solutions_fitnesses[i] > max_fitness) {
                max_fitness = solutions_fitnesses[i];
            }
            /*
            if(solutions_fitnesses[i] != 0) {
                printf("Item: %d\t", i);
                for (u32 j = 0; j < solutions_item_counts[i]; j += 1){
                    u32 idx = solutions_indices[i][j];
                    printf("Weight: %d Value: %d ", weights[idx], values[idx]);
                }
                printf("Fitness: %d", solutions_fitnesses[i]);
                printf("\n");
            }*/
        }
        f32 avg_fitness = (f32)sum_fitness / (f32)N;
        //printf("Generation: %d Best Fitness: %d Avg Fitness: %.2f \n", generation, max_fitness, avg_fitness); 
        printf("%d,%d,%.2f\n", generation, max_fitness, avg_fitness); 
        generation++;
    }
    
}