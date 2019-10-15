import BenchDataStructure from "../BenchDataStructure";
import {minHeap} from "datastructures-js";

class Heap<T> extends BenchDataStructure<T> {

    heap: minHeap;

    constructor() {
        super('HEAP', true);
        this.heap = minHeap();
    }

    public insert(value: T, index?: number) {
        this.heap.insert(value);
    }

    public pop(value?: T): T {
        return this.heap.extractMin();
    }

    public search = null;
}

export default Heap;
