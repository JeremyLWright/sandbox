/**
 * Brief: Red Black Tree Top Level 
 * Authors: Jeremy Wright <jeremy@codestrokes.com>
 * License: Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */    
import RedBlackNode;

class RedBlackTree {
    public:
        this()
        {
            nil = new RedBlackNode(0);
            nil.Left = nil;
            nil.Right = nil;
            nil.Parent = nil;
            nil.Color = RedBlackNode.Colors.BLACK;
            root = nil;
        }
        ~this(){ }

        unittest
        {
            assert(false);
        }

        invariant()
        {
            //Check the black height.
            
            //Traverse the graph, counting the black heights, at
            //each simple path, push the black height onto a stack.
            //At the end, assert all the black heights are equal.
            assert(false);
        }

        void Insert(int key)
        {
            RedBlackNode z = new RedBlackNode(key);
            RedBlackNode x = root;
            RedBlackNode y = nil;

           
            while(x != nil)
            {
                y = x;
                if(z.Key < z.Key)
                    x = x.Left;
                else
                    x = x.Right;
            }

            scope(failure)
            {
                //If the next insertion fails, we need to roll back the structure

            }

            z.Parent = y;
            if(y == nil)
                root = z;
            else if(z.Key < y.Key())
                y.Left = z;
            else
                y.Right = z;

            z.Left(nil);
            z.Right(nil);
            z.Color = RedBlackNode.Colors.RED;
            Insert_Fixup(z);

        }

        void Delete(int key)
        {
            RedBlackNode z = Search(key);
            RedBlackNode x;
            if(z == nil)
                return;

            RedBlackNode y = z;
            RedBlackNode.Colors original_color = y.Color;

            if(z.Left == nil)
            {
                x = z.Right;
                Transplant(z, z.Right());
            }
            else if(z.Right == nil)
            {
                x = z.Left;
                Transplant(z, z.Left());
            }
            else 
            {
                y = Minimum(z.Right);
                original_color = y.Color;
                x = y.Right;
                if(y.Parent == z)
                {
                    x.Parent = y;
                }
                else
                {
                    Transplant(y, y.Right);
                    y.Right = z.Right;
                    y.Right.Parent = y;
                }
                Transplant(z, y);
                y.Left = z.Left;
                y.Left.Parent = y;
                y.Color = z.Color;
            }
            
            if(original_color == RedBlackNode.Colors.BLACK)
            {
                Delete_Fixup(x);
            }
        }
        
    private:
        RedBlackNode Search(int key) const
        {
            return new RedBlackNode(key);
        }

        void Transplant(RedBlackNode u, RedBlackNode v)
        {
        }

        RedBlackNode Minimum(RedBlackNode x)
        {
            return x;
        }

        void Insert_Fixup(RedBlackNode z)
        {
        }

        void Delete_Fixup(RedBlackNode x)
        {
        }

        void Left_Rotate(RedBlackNode x)
        {
        }

        void Right_Rotate(RedBlackNode x)
        {
        }
        
        RedBlackNode nil;
        RedBlackNode root;
}

