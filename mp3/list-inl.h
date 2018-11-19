/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode* temp = head_;
  ListNode* curr = NULL;
  if(!empty()) {
    while(temp != NULL) {
      curr = temp->next;
      delete temp;
      temp = curr;
    }
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* insert = new ListNode(ndata);
  if(head_ == NULL)
    tail_ = insert;
  if(head_ != NULL)
    head_->prev = insert;
  insert->next = head_;
  insert->prev = NULL;
  head_ = insert;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* insert = new ListNode(ndata);

  if(tail_ == NULL)
    head_ = insert;
  if(tail_ != NULL)
    tail_->next = insert;
  insert->next = NULL;
  insert->prev = tail_;
  tail_ = insert;
  length_++;

}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1

  if(startPoint == NULL || startPoint == endPoint)
    return;

  ListNode* beforeStart = startPoint->prev;
  ListNode* afterEnd = endPoint->next;
  ListNode* curr = startPoint;
  ListNode *after, *before;

  while(curr != NULL && curr != afterEnd) {
    after = curr->next;
    before = curr->prev;

    curr->prev = after;
    curr->next = before;

    curr = curr->prev;
  }

  startPoint->next = afterEnd;
  endPoint->prev = beforeStart;

  if(beforeStart != NULL)
    beforeStart->next = endPoint;

  if(afterEnd != NULL)
    afterEnd->prev = startPoint;

  if(startPoint == head_)
    head_ = endPoint;
  if(endPoint == tail_)
    tail_ = startPoint;

  after = startPoint;
  startPoint = endPoint;
  endPoint = after;

return;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  ListNode* front = head_;
  ListNode* end = head_;

  if(n >= length_){
    reverse(head_, tail_);
    return;
  }

  for(int i = 0; i < length_; i+=n){
    for(int j = 1; j < n && end->next != NULL; j++)
      end = end->next;

    reverse(front, end);
    front = end->next;
    end = end->next;
  }

  return;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if(head_ != NULL){
    ListNode* curr = head_->next;
    ListNode* temp;

    while(curr != NULL && curr->next != NULL){
      T t = curr->data;
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
      insertBack(t);
      curr = curr->next->next;
    }
  }

}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2

  if(splitPoint <= length_ && splitPoint != 0){

    for(int i = 0; i < splitPoint; i++)
      start = start->next;

    if(start->prev != NULL)
      start->prev->next = NULL;
    start->prev = NULL;
  }

  return start;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  ListNode *ret, *temp1, *temp2;

  if(first == NULL)
    return second;

  if(second == NULL)
    return first;

  if(first->data < second->data)
    ret = first;
  else
    ret = second;

  while(first->next != NULL && second->next != NULL){
    while(first->data < second->data && first->next != NULL)
      first = first->next;

    temp2 = second->next;

    second->prev = first->prev;
    if(first->prev != NULL)
      first->prev->next = second;
    first->prev = second;
    second->next = first;

    second = temp2;

  }

  if(first->next == NULL){
    while(second->data < first->data && second->next != NULL)
      second = second->next;
    first->next = second;
    second->prev = first;
  }

  else if(second->next == NULL){
    while(first->data < second->data && first->next != NULL)
      first = first->next;
    first->prev->next = second;
    second->next = first;
    first->prev = second;
  }

  return ret;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  return NULL;
}
