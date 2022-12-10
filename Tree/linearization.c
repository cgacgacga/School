

Node* Linearize(Node* root) // returns the subtree's last node
{
    //if it's a leaf node
    if(root->left == NULL && root->right == NULL)
        return root;

    //if there is no left subtree
    if(root->left == NULL)
        return Linearize(root->right);

    //if there is no right subtree
    if(root->right == NULL)
    {
        root->right = root->left;
        root->left = NULL;
        return Linearize(root->right);
    }

    //both subtrees exist
    Node* left = root->left;
    Node* right = root->right;
    Node* lastOfLeft = Linearize(left);
    root->right = left;
    root->left = NULL;
    lastOfLeft->right = right;
    return Linearize(right);
}
