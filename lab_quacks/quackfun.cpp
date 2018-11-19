/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    if(s.empty())
      return T();
    if(s.size() == 1)
      return s.top();
    else{
      T top = s.top();
      s.pop();
      T ret = sum(s) + top;
      s.push(top);
      return ret;
    }

  //  return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * You are allowed only the use of one stack in this function, and no other local variables.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    stack<char> s;
    int size = input.size();
    for(int i = 0; i < size; i++){
      char curr = input.front();
      if(curr == '[')
        s.push(curr);
      if(curr == ']'){
        if(s.empty())
          return false;
        else if(s.top() != '[')
          return false;
        else
          s.pop();
      }
      input.pop();
    }
    // @TODO: Make less optimistic
    if(s.empty())
      return true;
    return false;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
  //make array that has all the values of q
  int size = q.size();
  T * var = new T[size];

  for( int i = 0; i<size; i++) {
    var[i]=q.front();
    q.pop();
  }

  int start=1;
  for(int num=1; start<size; num+=2){
    reverse(var, start, start+num, size);
    start+=2*num+3;
  }

  for (int i = 0; i < size; i++){
    q.push(var[i]);
  }

  delete [] var;
}


template <typename T>
void reverse(T* arr, int start, int end, int size){
if (start==end)
  return;

if(end>=size)
  end=size-1;

T temp;
while(start<end) {
  temp = arr[start];
  arr[start]=arr[end];
  arr[end]=temp;
  start++;
  end--;
}
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
  {
  T temp1, temp2;
  bool ret;

  //base case of empty stack returns true
  if(s.size()==0)
      return true;

  //store top of stack in temp1
  temp1 = s.top();
  s.pop();

  //recurse with smaller stack
  ret = verifySame(s,q);

  //restore stack to original values
  s.push(temp1);

  //if previous recursions returned true, check if top of stack
  //equals front of queue
  if(ret){
    if(s.top()==q.front()){
      temp2=q.front();

      //push front of queue to the back
      q.push(temp2);
      q.pop();
      return true;
    }
    //if not equal, return false
    else
      return false;
  }

  //if previous recursions false, return false
  else
    return false;
}

}

}
