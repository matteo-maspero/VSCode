/*
	@brief Computes the factorial of a number
	@param n The source number
	@return The factorial of n
*/
int factorial(int n) {
	if(n == 0)
		return 1;
	else
		return n * factorial(n - 1);
}

/*
	@brief Checks if a number is prime
	@param n The source number
	@return 1 if the number is prime, 0 otherwise
*/
int isPrime(int num) {
	if(num < 2)
		return 0;
	
	for(int i = 2; i * i <= num; i ++)
		if (!(num % i))
			return 0;

	return 1;
}

/*
	@brief Esegue la ricerca binaria dell'array
	@param arr L'array di interi
	@param target Il numero da cercare
	@param start L'indice di inizio della ricerca
	@param end L'indice di fine della ricerca
	@return The position of the target in the array or -1 if not found
*/
int binarySearch(int *arr, int target, int start, int end) {
	if(start > end)
		return -1;

	int mid = (start + end) / 2;

	if(arr[mid] == target)
		return mid;
	else if(arr[mid] < target)
		return binarySearch(arr, target, mid + 1, end);
	else
		return binarySearch(arr, target, start, mid - 1);
}

