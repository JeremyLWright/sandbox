/**
 * Brief: 
 * Authors: Jeremy Wright <jeremy@codestrokes.com>
 * License: Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */

class RedBlackNode {
    public:
    enum Colors { RED, BLACK };
    this(int Key)
    {
        key = Key;
    }
    ~this()
    {
    }

    unittest
    {
        auto root = new RedBlackNode(7);
        auto nil = new RedBlackNode(0);

        root.Left = new RedBlackNode(6);
        root.Right = new RedBlackNode(8);
        root.Left.Parent = root;
        root.Right.Parent = root;
        root.Right.Color = Colors.BLACK;
        root.Parent = nil;
        assert(root.Left.Key == 6);
        assert(root.Right.Key == 8);
        assert(root.isRed() == true);
        assert(root.Right.isRed() == false);
        assert(root.Left.isRed() == true);
        assert(root.Key == 7);
        assert(root.Right.Parent == root);
        assert(root.Left.Parent == root);

    }
    invariant()
    {
        assert(this.color == Colors.RED || this.color == Colors.BLACK);
        /* The parent should never be null, how can I check for this? */
    }
    
    bool isRed() 
    {
        return (color == Colors.RED);
    }
    @property {
        Colors Color()  { return color; }
        void Color(Colors new_color) { color = new_color; }
    }

    @property int Key() { return key; };
    
    /* What's wrong with this code?
     * RedBlackNode.d(34): Error: cannot implicitly convert expression (this.left) of type immutable(RedBlackNode) to RedBlackNode.RedBlackNode
     * 
    @property {
        RedBlackNode Left() immutable { return left; }
        void Left(RedBlackNode new_left) { left = new_left; }
    }
    */

    @property {
        RedBlackNode Left() { return left; }
        void Left(RedBlackNode new_left) { left = new_left; }
    }

    @property {
        RedBlackNode Right() { return right; }
        void Right(RedBlackNode new_right) { right = new_right; }
    }
    
    @property {
        RedBlackNode Parent() { return parent; }
        void Parent(RedBlackNode new_parent) { parent = new_parent; }
    }


    private:
    Colors color;
    int key;
    RedBlackNode parent;
    RedBlackNode left;
    RedBlackNode right;
}
