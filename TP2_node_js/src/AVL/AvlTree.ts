function compareTo(numb: number, numb2: number) {
    return numb > numb2 ? 1 : numb == numb2 ? 0 : -1
}

export abstract class AvlTree {
    readonly element: number;
    readonly left: AvlTree;
    readonly right: AvlTree;
    public readonly height: number;
    public readonly size: number;

    protected constructor(element: number, left: AvlTree, right: AvlTree, height: number, size: number) {
        this.element = element;
        this.left = left;
        this.right = right;
        this.height = height;
        this.size = size;
    }

    public abstract add(element: number): AvlTree;

    public abstract pollFirst(): Pair;

    public abstract remove(element: number): AvlTree;

    public abstract index(element: number): number;

    public abstract isLeaf() : boolean;

    public display(indent: string): string {
        return this.display("");
    }


    public abstract count();

    public abstract name();

}

class Pair {
    public readonly first: number;
    public readonly second: AvlTree;

    public constructor(first: number, second: AvlTree) {
        this.first = first;
        this.second = second;
    }
}

export class AVLNil extends AvlTree {
    public constructor() {
        super(null, null, null, 0, 0);
    }

    public add(element: number): AvlTree {
        return <any>(new AVLNode(element, this, this));
    }

    public pollFirst(): Pair {
        return <any>(new Pair(null, this));
    }

    public remove(element: number): AvlTree {
        return this;
    }

    public index(element: number): number {
        return 0;
    }

    public subSize(fromElement: number, toElement: number): number {
        return 0;
    }

    public display(indent: string): string {
        return indent + "$\n";
    };
    public isLeaf() : boolean{
        return true;
    }

    public count() : number {
        let sum = 0;
        if(this.left !== null){
            sum+=this.left.count();
        }
        if(this.right !== null){
            sum+=this.right.count();
        }
        return sum+1;
}

    name() {
        return "AVL NIL";
    }
}

export class AVLNode extends AvlTree {
    public constructor(element: number, left: AvlTree, right: AvlTree) {
        super(element, left, right, Math.max(left.height, right.height) + 1, left.size + right.size + 1);
    }

    private balanceLeft(element: number, left: AvlTree, right: AvlTree): AvlTree {
        if (left.height <= right.height + 1) {
            return <any>(new AVLNode(element, left, right));
        } else if (left.left.height > right.height) {
            return <any>(new AVLNode(left.element, left.left, <any>(new AVLNode(element, left.right, right))));
        } else {
            return <any>(new AVLNode(left.right.element, <any>(new AVLNode(left.element, left.left, left.right.left)), <any>(new AVLNode(element, left.right.right, right))));
        }
    }


    private balanceRight(element: number, left: AvlTree, right: AvlTree): AvlTree {
        if (left.height + 1 >= right.height) {
            return <any>(new AVLNode(element, left, right));
        } else if (left.height < right.right.height) {
            return <any>(new AVLNode(right.element, <any>(new AVLNode(element, left, right.left)), right.right));
        } else {
            return <any>(new AVLNode(right.left.element, <any>(new AVLNode(element, left, right.left.left)), <any>(new AVLNode(right.element, right.left.right, right.right))));
        }
    }


    add(element: number): AvlTree {
        let c: number = compareTo(element, this.element);
        if (c < 0) {
            let left: AvlTree = this.left.add(element);
            if (left !== this.left) {
                return this.balanceLeft(this.element, left, this.right);
            }
        } else if (c > 0) {
            let right: AvlTree = this.right.add(element);
            if (right !== this.right) {
                return this.balanceRight(this.element, this.left, right);
            }
        }
        return this;
    }

    index(element: number): number {
        return 0;
    }

    pollFirst(): Pair {
        if(this.left != null && this.left instanceof <any>AVLNil) {
            return <any>(new Pair(this.element, this.right));
        } else {
            let p : Pair = this.left.pollFirst();
            return <any>(new Pair(p.first, this.balanceRight(this.element, p.second, this.right)));
        }
    }

    remove(element: number): AvlTree {
        let c: number = compareTo(element, this.element);
        if(c < 0) {
            let left : AvlTree = this.left.remove(element);
            if(left !== this.left) {
                return this.balanceRight(this.element, left, this.right);
            }
        } else if(c > 0) {
            let right : AvlTree = this.right.remove(element);
            if(right !== this.right) {
                return this.balanceLeft(this.element, this.left, right);
            }
        } else if(this.right != null && this.right instanceof <any>AVLNil) {
            return this.left;
        } else {
            let p : Pair = this.right.pollFirst();
            return this.balanceLeft(p.first, this.left, p.second);
        }
        return this;
    }

    public display(indent: string): string {
        const indent1: string = indent + "  ";
        return this.left.display(indent1)
            + indent + this.element + "\n"
            + this.right.display(indent1);
    }

    public isLeaf() : boolean{
        return false;
    }

    public count() : number {
        return 1;
    }

    name() {
        return "AVL NODE";
    }
}
