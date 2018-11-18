public void DSW() {
  if (null != root) {
    createBackbone();// effectively: createBackbone( root)
    createPerfectBST();//effectively: createPerfectBST( root)
  }
}
 
/**
 * Time complexity: O(n)
 */
private void createBackbone() {
  Node grandParent = null;
  Node parent = root;
  Node leftChild;
 
  while (null != parent) {
    leftChild = parent.left;
    if (null != leftChild) {
      grandParent = rotateRight(grandParent, parent, leftChild);
      parent = leftChild;
    } else {
      grandParent = parent;
      parent = parent.right;
    }
  }
}
 
/************************************************************************
 *   Before      After
 *    Gr          Gr
 *     \           \
 *     Par         Ch
 *    /  \        /  \
 *   Ch   Z      X   Par
 *  /  \            /  \
 * X    Y          Y    Z
 ***********************************************************************/
private Node rotateRight(Node grandParent, Node parent, Node leftChild) {
  if (null != grandParent) {
    grandParent.right = leftChild;
  } else {
    root = leftChild;
  }
  parent.left = leftChild.right;
  leftChild.right = parent;
  return grandParent;
}
 
/**
 * Time complexity: O(n)
 */
private void createPerfectBST() {
  int n = 0;
  for (Node tmp = root; null != tmp; tmp = tmp.right) {
    n++;
  }
  //m = 2^floor[lg(n+1)]-1, ie the greatest power of 2 less than n: minus 1
  int m = greatestPowerOf2LessThanN(n + 1) - 1;
  makeRotations(n - m);
 
  while (m > 1) {
    makeRotations(m /= 2);
  }
}
 
/**
 * Time complexity: log(n)
 */
private int greatestPowerOf2LessThanN(int n) {
  int x = MSB(n);//MSB
  return (1 << x);//2^x
}
 
/**
 * Time complexity: log(n)
 * return the index of most significant set bit: index of
 * least significant bit is 0
 */
public int MSB(int n) {
  int ndx = 0;
  while (1 < n) {
    n = (n >> 1);
    ndx++;
  }
  return ndx;
}
 
private void makeRotations(int bound) {
  Node grandParent = null;
  Node parent = root;
  Node child = root.right;
  for (; bound > 0; bound--) {
    try {
      if (null != child) {
        rotateLeft(grandParent, parent, child);
        grandParent = child;
        parent = grandParent.right;
        child = parent.right;
      } else {
        break;
      }
    } catch (NullPointerException convenient) {
      break;
    }
  }
}
 
private void rotateLeft(Node grandParent, Node parent, Node rightChild) {
  if (null != grandParent) {
    grandParent.right = rightChild;
  } else {
    root = rightChild;
  }
  parent.right = rightChild.left;
  rightChild.left = parent;
}
