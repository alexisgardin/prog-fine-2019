import BenchDataStructure from "../BenchDataStructure";
import {AvlTree} from "@tyriar/avl-tree";

class AVL<T> extends BenchDataStructure<T> {

    avl: AvlTree<T, T>;

    constructor() {
        super('AVL', true);
        this.avl = new AvlTree();
    }

    public insert(value: T, index?: number) {
        this.avl.insert(value);
    }

    public pop(value?: T): any {
        return this.avl.delete(value);
    }

    public search(value: T): T {
        return this.avl.get(value);
    }
}

export default AVL;
