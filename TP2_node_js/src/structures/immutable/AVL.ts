import BenchDataStructure from "../BenchDataStructure";
import {AVLNil, AvlTree} from "../custom/AVL/AvlTree";

class AVL<T> extends BenchDataStructure<T> {

    avl: AvlTree;

    constructor() {
        super('AVL', false);
        this.avl = new AVLNil();
    }

    public insert(value: any, index?: number) {
        this.avl = this.avl.add(value);
    }

    public pop(value?: any): any {
        this.avl = this.avl.remove(value);
        return this.avl.element;
    }

    public search(value: any): any {
        return this.avl.find(value);
    }
}

export default AVL;
