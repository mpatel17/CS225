/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if(t==NULL || t->right==NULL)
      return;

    Node *r = t->right, *rl = t->right->left;
    t->right = rl;
    r->left = t;
    t = r;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    if(t==NULL || t->left==NULL)
      return;

    Node *l = t->left, *lr = t->left->right;
    t->left = lr;
    l->right = t;
    t = l;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    Node *lp=NULL, *rp=NULL, *rlp=NULL, *lrp=NULL;
    if(subtree->left!=NULL)
      lp = subtree->left;

    if(subtree->right!=NULL)
      rp = subtree->right;

    if(rp!=NULL && rp->left!=NULL)
      rlp = rp->left;

    if(lp!=NULL && lp->right!=NULL)
      lrp = lp->right;

    // your code here

    //right heavy and left leaning
    if( (getHeightBalance(subtree)<-1) && (getHeightBalance(subtree->right)>-1) ){
      rotateRightLeft(subtree);
      subtree->height = height(subtree);

      if(lp!=NULL)
        lp->height = height(lp);
      if(rp!=NULL)
        rp->height = height(rp);
      if(rlp!=NULL)
        rlp->height = height(rlp);
      if(lrp!=NULL)
        lrp->height = height(lrp);
    }

    //left heavy and right leaning
    else if( (getHeightBalance(subtree)>1) && (getHeightBalance(subtree->left)<1) ){
      rotateLeftRight(subtree);
      subtree->height = height(subtree);

      if(lp!=NULL)
        lp->height = height(lp);
      if(rp!=NULL)
        rp->height = height(rp);
      if(rlp!=NULL)
        rlp->height = height(rlp);
      if(lrp!=NULL)
        lrp->height = height(lrp);
    }

    //right heavy
    else if( getHeightBalance(subtree)<-1 ){
      rotateLeft(subtree);
      subtree->height = height(subtree);

      if(lp!=NULL)
        lp->height = height(lp);
      if(rp!=NULL)
        rp->height = height(rp);
      if(rlp!=NULL)
        rlp->height = height(rlp);
      if(lrp!=NULL)
        lrp->height = height(lrp);
    }

    //left heavy
    else if( getHeightBalance(subtree)>1){
      rotateRight(subtree);
      subtree->height = height(subtree);

      if(lp!=NULL)
        lp->height = height(lp);
      if(rp!=NULL)
        rp->height = height(rp);
      if(rlp!=NULL)
        rlp->height = height(rlp);
      if(lrp!=NULL)
        lrp->height = height(lrp);
    }


}

template <class K, class V>
int AVLTree<K, V>::getHeightBalance(Node* subtree) {
  // your code here
  if(subtree==NULL)
    return 0;

  return height(subtree->left) - height(subtree->right);
}

template <class K, class V>
int AVLTree<K, V>::height(Node* subtree){
  if(subtree==NULL){
    return -1;
  }
  if(subtree->right==NULL && subtree->left==NULL){
    return 0;
  }
  return 1 + std::max(height(subtree->left),height(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if(root==NULL){
      root = new Node(key, value);
      return;
    }

    if(key <= subtree->key){
      subtree->height++;

      if(subtree->left == NULL){
        subtree->left= new Node(key, value);
      }

      else{
        insert(subtree->left, key, value);
      }
    }

    else if (key > subtree->key){
      subtree->height++;
      if(subtree->right == NULL){
        subtree->right= new Node(key, value);
      }

      else{
        insert(subtree->right, key, value);
      }
    }

    //if(subtree==root){
      rebalance(subtree);
    //}
}

template <class K, class V>
void AVLTree<K, V>::balance(Node* subtree){
  if(subtree==NULL)
    return;

  balance(subtree->left);
  balance(subtree->right);
  rebalance(subtree);
}



template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        subtree->height--;
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        subtree->height--;
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree=NULL;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* curr = subtree->left, *prev = subtree->left;

            while (curr->right != NULL){
              prev = curr;
              curr = curr->right;
            }

            /*if (curr != prev){
              prev->right = NULL;
              curr->left = subtree->left;
            }

            curr->right = subtree->right;
            delete subtree;
            subtree = curr;*/
            swap(curr, subtree);

            if(curr != prev)
              prev->right=NULL;

            else
              subtree->left=curr->left;

            delete curr;

        } else {
            /* one-child remove */
            // your code here
            Node * temp;

            if(subtree->left!=NULL)
              temp = subtree->left;

            else
              temp= subtree->right;

            delete subtree;
            subtree=temp;
        }
        // your code here
        //cout<<subtree;
        //rebalance(subtree);
        //cout<<"donezo";
    }
}
/*
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            // your code here
            Node* pre = subtree->left;
            Node* prev = subtree->left;
            while (pre->right != NULL){
              prev = pre;
              pre = pre->right;
            }
            if (pre != prev){
              prev->right = NULL;
              pre->left = subtree->left;
            }
            pre->right = subtree->right;
            delete subtree;
            subtree = pre;
        } else {
            // your code here
            if (subtree->right != NULL){
              Node* temp = subtree->right;
              delete subtree;
              subtree = temp;
            } else {
              Node* temp = subtree->left;
              delete subtree;
              subtree = temp;
            }

        }
        // your code here
        rebalance(subtree);
        heightUpdate(subtree);
    }*/
