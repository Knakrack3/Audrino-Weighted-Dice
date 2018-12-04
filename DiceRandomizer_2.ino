/* All code here is made by Matthew Clark
 * However, credit to stack overflow for coming up with some ways to fix bugs that my carlessness caused
 */ 
 double weights[6] = {1, 7, 5, 1, 1, 1};  //This is where you adjust the probability. The first slot corrosponds to 1 on the die, and the last slot corrosponds to 6 on the die
// Indexing starts at zero, so the first value has an index of zero, the second one has an index of 1, then 2, etc.
double Probs[6] = {1, 1, 1, 1, 1, 1}; // This is declared as a global variable, as you can't return arrays in c. This should not be edited.
double GlobSum = 0; // There's probably more of an efficient way of doing this than making it a global variable, but we be do it like that
double sum(double arr[], double n) {
  /*
   * This function take the sum of an array passed into it arr[], the size of which must be passed as n.
   * There is no way to get the size of an array in c, so it must be inputted as a constant
   */
    double sum = 0; //sum is a local double, which can support decimal values. This increases the size of the file, so you should use int if you are not using decimals. We are, so we use double here
    for (int i=0; i<n; i++) 
   /* A for loop has three conditions: an initalized variable (int i=0), which creates a new integer, a condition (i<n), which keeps the loop going until the condition is met
    * and the increment (i++), which happens each time the end of the loop is reach. The lines inside the for loop keep going until the condion is met.
    * In this case, the loop will go n times. i++ adds one to i every time the loop is ended. It is important to note that i starts at 0
    */
    {
        sum += arr[i];  //Adds the value of array slot i to sum. 
        // Why does i start at zero and not one? Because the first slot of the array is actually accessed by arr[0], not arr[1].
    }
    return sum; /*This returns the sum value. For instance, if we had the formula double u = sum(weights, 6);
* it would create a new double type variable named u, then run the function sum. Since it returns the value sum at the end of the function,
* u would be set to what is returned. (If weights was {1, 1, 1, 1, 1, 1}, it would be 6, for example) 
* It is important to note that arr[] and n must be defined as doubles in the () of the function, or else the computer would yell at you forever
    */
}
double parsearray(double arr[], double n) {
  /* This function would probably be better as a void, as it has no output, but oh well.
   * What this basically does, is it divides each entry in the array weights by the sum of all the entries, and then multiplies each entry by 100.
   * It then stores the new value in the respective entry in the array Probs.
   * This function is the reason we are using doulbes instead of integers, as integers can not store decimal values, and we want this to be as exact as possible
   * the number n is how many values are in the array, in our case 6. Why not just change every case of n to 6? Well what if we want this to be a 7 sided die?
   */
 double add = sum(arr, n); //calls sum function with the passed array, in our case weights, and sets a new double variable add to that.
// Debug code (for use with c compiler w/ console) printf("Sum Equals: %f", add);
// Debug code (for use with c compiler w/ console) printf("\r\n");
// Debug code (for use with c compiler w/ console) printf("Probabilities are: ");
 for (int i=0; i<n; i++) { //for loop 
     Probs[i]=(arr[i]/add)*100; //Sets index i of Probs to passed index i of arr divided by add, times 100.
     // for instance, if index 0 of arr was 2, and the sum was 10, then index 0 of probs would be 20.000000
     // it is important to remember that arrays start their index at zero, not 1
// Debug code (for use with c compiler w/ console)    printf("%f, ", ((arr[i]/add)*100))  
 }
}
double Parseprobs(double arr[], double n) {
  /* This parses the passed array, and the array size n, to mean values so we can use random whole numbers instead of decimals, because ranomizing decimals is much more tedious than randomizing whole numbers
   *  Basicallyy what it does is multiplies each index of the passed array by 100000, percisley enough to make it a whole number, then sets the global
   * variable GlobSum the sum of all the values, which should be equal to 10,000,000
   */
// Debug code (for use with c compiler w/ console)   printf("\n New Probabilities are: ");
    for(int i=0; i<n; i++) {
        Probs[i]=Probs[i]*100000;
// Debug code (for use with c compiler w/ console)        printf("%f, " , Probs[i]);
    }
    GlobSum = sum(Probs, n);
// Debug code (for use with c compiler w/ console)    printf("\n GlobSum = %f", GlobSum);

}
double RollDie(double arr[], double n, double siz) {
  /* This rolles our random number from one to size with a passed array.
   * I think this method is quite ingenious, i'll comment ecah line individually
   * n is the GlobSum, siz is the size of arr
   */
randomSeed(215); //Change random seed for different results, otherwise randomization will follow a predictable pattern
double r = random(1, n); //creates a random number from one to n, which in most cases should be 10,000,000
for (int i=0; i<siz; i++){ //go through six times, from 0 to 5
    if (r >= sum(arr, i) && r < sum(arr, (i+1)) || i == (siz-1))
    /* This kind of abuses a bug in the summing array software, but who cares. It's a feature now.
     * If the random number is between the sum of the passed array with the index values from i-1 and i+1, then it returns i+1, because arrays start at zero, otherwise it incriments
     * The bug is that if i is 0, the sum(arr, i) returns zero. I was hoping to not build a catch for that, so that's great
     * Also, if i is 5, it automatically returns six for a catch-all if the ranomizer messes up
     * && means and for if statments, || means or
     * This also can be used with any size array, but the explanation is for the standard size of six.
     */
    { 
        return i+1;
    }
}
return -4; //You should never get here
}
void setup() {
    parsearray(weights, 6); //uses function parsearray to generate the basic probabilties list
    Parseprobs(Probs, 6); //uses function Parseprobs to generate the basic probs list
    //Those two functions only need to be made once, so they can stay in the setup.
    double rolled = RollDie(Probs, GlobSum, 6);   //makes new local double variable (called rolled), and sets that number from 1 to 6 based on the weights and the random number. Obiously, the numbers with higher weights will be called more often.
}
void loop() {

  }
