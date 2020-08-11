/* bankAccount.h simulates a simple bank account
 *
 * Joel Adams, Calvin College, Fall 2013.
 */
//By creating a lock variable that will explicitly lock and unlock when calling both the deposit
//and withdraw functions from the header file

// Shared Variables
double bankAccountBalance = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// add amount to bankAccountBalance
void deposit(double amount) {
	pthread_mutex_lock(&lock);
	bankAccountBalance += amount;
	pthread_mutex_unlock(&lock);
}

// subtract amount from bankAccountBalance
void withdraw(double amount) {
	pthread_mutex_lock(&lock);
   bankAccountBalance -= amount;
   pthread_mutex_unlock(&lock);
}

void cleanup() {
}

