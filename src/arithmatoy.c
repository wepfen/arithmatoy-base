#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int VERBOSE = 0;

const char *get_all_digits() { return "0123456789abcdefghijklmnopqrstuvwxyz"; }
const size_t ALL_DIGIT_COUNT = 36;

void arithmatoy_free(char *number) { free(number); }

char *arithmatoy_add(unsigned int base, const char *lhs, const char *rhs) {
  // Fill the function, the goal is to compute lhs + rhs
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result

	//TODO gérer pour le cas verbose
	char *result;

	lhs = drop_leading_zeros(lhs);
	rhs = drop_leading_zeros(rhs);

	int len_lhs = strlen(lhs);
	int len_rhs = strlen(rhs);
	
	int max_value = base;
	int max_len = 0;
	int carry = 0;
	char *my_lhs = strdup(lhs);
	char *my_rhs = strdup(rhs);
	char *rev_rhs = reverse(my_rhs);
	char *rev_lhs = reverse(my_lhs);
	int tmp = 0;

	if (VERBOSE) {
		fprintf(stderr, "add %s %s --verbose\n", lhs, rhs);
		fprintf(stderr, "%s + %s\n", lhs, rhs);
		fprintf(stderr, "add: entering function\n");
	}

	max_len = get_max_len(len_lhs, len_rhs);	
	result = malloc(len_rhs+2); // 2 for '\0' and for a probable sign idk
	
	for (int counter = 0; counter < max_len; counter++ )
	{
	    tmp = 0;

		if (VERBOSE){
			fprintf(stderr, "add: digit %c digit %c carry %d\n",  (len_lhs>counter ?rev_lhs[counter] : '0'),  (len_rhs>counter ?rev_rhs[counter] : '0'), carry);
		}

		if (len_lhs>counter)
			tmp += get_digit_value(rev_lhs[counter]); //convertit char en savaleur en chiffre
			
		if (len_rhs>counter)
			tmp += get_digit_value(rev_rhs[counter]);
		
		if (carry)
		{
			tmp += carry;
			carry = 0;
		}
		if (tmp >= max_value)
		{	
			carry = tmp/base; 
			tmp = tmp - base * carry;
		}
		
		if (VERBOSE){
			fprintf(stderr, "add: result: digit %d carry %d\n", tmp, carry);
		}

		result[counter] = to_digit(tmp);
		if (counter+1==max_len && carry == 1){
			result[max_len] = '1';	
			max_len+=1;
			if (VERBOSE){
				fprintf(stderr, "add: add final carry %d", carry);
			}
		}
		// teste si rev_lhs[i] == NULL, si oui ajouter 0, sinon ajouter sa get_digit value
		// pareil avec rev_rhs
	}

	reverse(result);
	result[max_len] = '\0';
	return result;

}

char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs) {
	
	if (VERBOSE) {
		fprintf(stderr, "sub %s %s --verbose\n", lhs, rhs);
		fprintf(stderr, "%s - %s\n", lhs, rhs);
		fprintf(stderr, "sub: entering function\n");
	}
	
	// Fill the function, the goal is to compute lhs - rhs (assuming lhs > rhs)
  	// You should allocate a new char* large enough to store the result as a
  	// string Implement the algorithm Return the result
	char *result;
	lhs = drop_leading_zeros(lhs);
	rhs = drop_leading_zeros(rhs);
	int len_lhs = strlen(lhs);
	int len_rhs = strlen(rhs);

	int max_value = base;
	int max_len = 0;
	int carry = 0;
	char *my_lhs = strdup(lhs);
	char *my_rhs = strdup(rhs);
	char *rev_rhs = reverse(my_rhs);
	char *rev_lhs = reverse(my_lhs);
	int tmp = 0;
	
	//printf("lhs character : %s, rhs character : %s\n", lhs, rhs);
	//printf("strlen lhs : %d\n", strlen(lhs));

	// if maudit
	if (strlen(lhs) == strlen(rhs)) {

		// check si rhs > lhs lorsque leur longueur est égale
		if(get_digit_value(lhs[0])<get_digit_value(rhs[0])){
			return NULL;

		} else if (strlen(lhs)!=1){
		// pour le cas lhs == rhs == 0
		} else if (strlen(lhs) == 1){
			if (strcmp("0", rhs) == strcmp("0", lhs)){
				printf("ca passe la jsp pq\n");
				return "0";
			}
		}
	}
	// si lhs est plus grand ou égal, alloue de l'espace mémoire
	
	if (len_lhs >= len_rhs) {
		max_len = len_lhs;
		result = malloc(len_lhs+2); // 2 for '\0' and for a probable sign idk
		
	// check si la longueur de rhs supérieure à lhs
	} else if (len_rhs > len_lhs) {
		
		return NULL;
	}

	
	
	
	for (int counter = 0; counter < max_len; counter++ )
	{
	    tmp = 0;

		if (VERBOSE){
			fprintf(stderr, "sub: digit %c digit %c carry %d\n",  (len_lhs>counter ?rev_lhs[counter] : '0'),  (len_rhs>counter ?rev_rhs[counter] : '0'), carry);
		}

		if (len_lhs>counter)
			tmp += get_digit_value(rev_lhs[counter]); //ajoute la lhs
		
			
		if (len_rhs>counter)
			tmp -= get_digit_value(rev_rhs[counter]); // sous trait la rhs

		if (carry)
		{
			tmp -= carry;
			carry = 0;
		}

		if (tmp < 0) //si le caluler devient négatif, 
		{
			tmp += base;
			carry += 1;
		}

		if (VERBOSE){
			fprintf(stderr, "sub: result: digit %d carry %d\n", tmp, carry);
		}

		result[counter] = to_digit(tmp);
		// teste si rev_lhs[i] == NULL, si oui ajouter 0, sinon ajouter sa get_digit value
		// pareil avec rev_rhs
	}

	reverse(result);
	result[max_len] = '\0';
	char *true_result = drop_leading_zeros(result);
	true_result[strlen(result)] = '\0';
	

	//printf("result : %s\n", result);
	
	return true_result;
}

char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "mul: entering function\n");
  }

  // Fill the function, the goal is to compute lhs * rhs
  // You should allocate a new cha#include <stddef.h>

// Here are some utility functions that might be helpful to implement add, sub
// and mul:
}


unsigned int get_digit_value(char digit) {
  // Convert a digit from get_all_digits() to its integer value
  if (digit >= '0' && digit <= '9') {
    return digit - '0';
  }
  if (digit >= 'a' && digit <= 'z') {
    return 10 + (digit - 'a');
  }
  return -1;
}

char to_digit(unsigned int value) {
  // Convert an integer value to a digit from get_all_digits()
  if (value >= ALL_DIGIT_COUNT) {
    debug_abort("Invalid value for to_digit()");
    return 0;
  }
  return get_all_digits()[value];
}

char *reverse(char *str) {
  // Reverse a string in place, return the pointer for convenience
  // Might be helpful if you fill your char* buffer from left to right
  const size_t length = strlen(str);
  const size_t bound = length / 2;
  for (size_t i = 0; i < bound; ++i) {
    char tmp = str[i];
    const size_t mirror = length - i - 1;
    str[i] = str[mirror];
    str[mirror] = tmp;
  }
  return str;
}

const char *drop_leading_zeros(const char *number) {
  // If the number has leading zeros, return a pointer past these zeros
  // Might be helpful to avoid computing a result with leading zeros
  if (*number == '\0') {
    return number;
  }
  while (*number == '0') {
    ++number;
  }
  if (*number == '\0') {
    --number;
  }
  return number;
}

void debug_abort(const char *debug_msg) {
  // Print a message and exit
  fprintf(stderr, debug_msg);
  exit(EXIT_FAILURE);
}

int get_max_len(int len_lhs, int len_rhs){
		
	if (len_lhs > len_rhs) {
		return len_lhs;
	} else {
		return len_rhs;
	}
}

/*
int main(void){
	
	printf("\n\n##### Base 10 : 10 - 5 #####\n");	
	char* res = arithmatoy_sub(10, "10", "5");
	printf("correct ? %d\n", atoi(res) == (10-5));	
	printf("result : %s\n", res);

	//arithmatoy_free(res);

    return 0;
}
*/