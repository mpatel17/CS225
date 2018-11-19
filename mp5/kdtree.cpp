/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

/**returns true if first smaller than second in the specified dimensions
 * ties broken with < operator*/

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if( first[curDim] == second[curDim] )
      return first < second;

    else
      return first[curDim] < second[curDim];
}

/* determines if potential point is "closer" than current best points
 * return true if it is*/
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double sumC=0;
     double sumP=0;
     for(int i =0; i<Dim; i++){
       sumC+=( pow( target[i]-currentBest[i] , 2.0 ) );
       sumP+=( pow( target[i]-potential[i] , 2.0 ));
     }

     if(sumC==sumP)
      return potential<currentBest;

    else
      return sumP < sumC;
}

/* algorithm to pick the median element in array, returns its index */
template <int Dim>
int KDTree<Dim>::quickselect(int k, int left, int right, int currDim, vector<Point<Dim>> &newPoints){

  if(left==right)
    return left;

  int piv = (left+right)/2;
  piv = partition(left, right, currDim, piv, newPoints);
  if(k==piv)
    return k;

  if(k<piv)
    return quickselect(k, left, piv-1, currDim, newPoints);

  else
    return quickselect(k, piv+1, right, currDim, newPoints);

}

/* helper function for quickselect, partitions elements around pivot in array*/
template <int Dim>
int KDTree<Dim>::partition(int left, int right, int currDim, int pivotIndex, vector<Point<Dim>> &list){
  Point<Dim> pivotVal = list[pivotIndex];

  Point<Dim> temp = list[right];
  list[right] = list[pivotIndex];
  list[pivotIndex]=temp;

  int storeIndex=left;

  for(int i = left; i<right; i++){

    if( smallerDimVal(list[i], pivotVal, currDim) ){
      temp = list[i];
      list[i] = list[storeIndex];
      list[storeIndex]=temp;
      storeIndex++;
    }
  }

  temp = list[storeIndex];
  list[storeIndex] = list[right];
  list[right]=temp;

  return storeIndex;
}

/*constructor for creating KD tree given a vector of points*/
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

     vector<Point<Dim>> copyPoints = newPoints;
     size = newPoints.size();

     //if size not 0 do all this
     if(size != 0){
       //pick middle index
       //int midIdx = quickselect((size-1)/2, 0, size-1, 0, copyPoints);
       //root = new KDTreeNode(copyPoints[midIdx]);
       createTree(root, 0, size-1, 0, copyPoints);
     }

     //if array size is 0, root is null youre done
     else{
       root=NULL;
     }

}

template <int Dim>
void KDTree<Dim>::createTree(KDTreeNode * &node, int beg, int end, int dimC, vector<Point<Dim>>& newPoints){
  //if there is only 1 element in range, it is middle and therefore you done
  if(beg==end){
    node = new KDTreeNode(newPoints[beg]);
    return;
  }

  //dimension being compared
  dimC = dimC%(Dim);

  //middle index from current range
  int mid = quickselect( (beg+end)/2, beg, end, dimC, newPoints);

  if(beg+1==end){
    node=new KDTreeNode(newPoints[beg]);
    node->right= new KDTreeNode(newPoints[end]);
    return;
  }

  //else do all this

  node = new KDTreeNode(newPoints[mid]);


  //mid index from left and right subportions
  int left = quickselect( (beg+mid-1)/2, beg, mid-1, dimC, newPoints);
  int right = quickselect( (mid+end+1)/2, mid+1, end, dimC, newPoints);

  //put mid index point in correct node (left or right)
  if( smallerDimVal(newPoints[left], newPoints[right], dimC) ){
    createTree(node->left, beg, mid-1, dimC+1, newPoints);
    createTree(node->right, mid+1, end, dimC+1, newPoints);
  }

  else {
    createTree(node->right, beg, mid-1, dimC+1, newPoints);
    createTree(node->left, mid+1, end, dimC+1, newPoints);
  }

}

/*
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{


     vector<Point<Dim>> copyPoints = newPoints;
     size = newPoints.size();

     //if size not 0 do all this
     if(size != 0){
       //pick middle index
       int midIdx = quickselect((size-1)/2, 0, size-1, 0, copyPoints);

       //create root and recurse through tree inputting nodes
       root = new KDTreeNode( copyPoints[midIdx] );
       createTree(root, 0, size-1, 0, copyPoints);
     }

     //if array size is 0, root is null youre done
     else{
       root=NULL;
     }

}

template <int Dim>
void KDTree<Dim>::createTree(KDTreeNode * node, int beg, int end, int dimC, vector<Point<Dim>>& newPoints){
  //if there is only 1 element in range, it is middle and therefore you done
  if(beg>=end)
    return;

  //dimension being compared
  int dimComp = dimC%(Dim);

  //middle index from current range
  int mid = quickselect( (beg+end)/2, beg, end, dimComp, newPoints);

  //if two elements in range, end goes on the right and then you are done
  if(beg+1==end){
    node->right=new KDTreeNode(newPoints[end]);
    return;
  }

  //else do all this

  //mid index from left and right subportions
  int left = quickselect( (beg+mid-1)/2, beg, mid-1, dimComp, newPoints);
  int right = quickselect( (mid+end+1)/2, mid+1, end, dimComp, newPoints);

  //put mid index point in correct node (left or right)
  if( smallerDimVal(newPoints[left], newPoints[right], dimComp) ){
    node->left=new KDTreeNode(newPoints[left]);
    node->right=new KDTreeNode(newPoints[right]);
  }

  else {
    node->left=new KDTreeNode(newPoints[right]);
    node->right=new KDTreeNode(newPoints[left]);
  }

  //recursively keep creating
  createTree(node->left, beg, mid-1, dimC+1, newPoints);
  createTree(node->right, mid+1, end, dimC+1, newPoints);
}
*/





template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other): root(copy(other.root)) {
  /**
   * @todo Implement this function!
   */
   size=other.size;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
   size=rhs.size;

   if (this != &rhs) {
      clear(root);
      root = copy(rhs.root);
  }

  return *this;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * node) {
  if(node==NULL)
    return;

  clear(node->left);
  clear(node->right);

  delete node;
}

template <int Dim>
void KDTree<Dim>::clear() {
  clear(root);
  root=NULL;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::copy(KDTreeNode * node) {
  if (node == NULL)
      return NULL;

  // Copy this node and it's children
  KDTreeNode* newNode = new KDTreeNode(node->point);
  newNode->left = copy(node->left);
  newNode->right = copy(node->right);
  return newNode;
}





template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return findNearestNeighbor(query, NULL, root, 0)->point;

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode *closestPoint, KDTreeNode *currentPoint, int dimension) const
{
  //set dimension right
  dimension%=Dim;

  //if left child exists and if we need to traverse to the left node (before backtracking)
  if(smallerDimVal(query, currentPoint->point, dimension) && currentPoint->left!=NULL){
    closestPoint = findNearestNeighbor(query, closestPoint, currentPoint->left, dimension+1);
  }

  //else if right child exists and if we need to traverse to the right node (before backtracking)
  else if(!smallerDimVal(query, currentPoint->point, dimension) && currentPoint->right!=NULL) {
    closestPoint = findNearestNeighbor(query, closestPoint, currentPoint->right, dimension+1);
  }

  //if first time reaching leaf and closest point hasnt been set, it equals the leaf
  if(closestPoint == NULL)
    closestPoint = currentPoint;

  else if( shouldReplace(query, closestPoint->point, currentPoint->point) )
    closestPoint=currentPoint;


  double radius=0;
  for(int i = 0; i<Dim; i++)
    radius+=( pow( closestPoint->point[i]-query[i] , 2.0 ) );

  radius = sqrt(radius);

  //check if current point should replace closest point
  if( abs(currentPoint->point[dimension] - query[dimension]) <= radius ){

    if(smallerDimVal(query, currentPoint->point, dimension) && currentPoint->right!=NULL)
      closestPoint = findNearestNeighbor(query, closestPoint, currentPoint->right, dimension+1);

    else if(!smallerDimVal(query, currentPoint->point, dimension) && currentPoint->left!=NULL)
      closestPoint = findNearestNeighbor(query, closestPoint, currentPoint->left, dimension+1);

  }

  return closestPoint;
}
