import BenchDataStructure from "../BenchDataStructure";
import MinHeap from "../custom/Heap/MinHeap";

class Heap<T> extends BenchDataStructure<T> {

    heap: MinHeap;

    constructor() {
        super('HEAP', false);
        this.heap = new MinHeap();
    }

    public insert(value: any, index?: number) {
        this.heap.add(value);
    }

    public pop(value?: T): any {
        return this.heap.removeRoot();
    }

    public search = null;
}

export default Heap;
