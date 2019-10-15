import BenchDataStructure from "../BenchDataStructure";
import {queue} from "datastructures-js";

class Queue<T> extends BenchDataStructure<T> {

    queue: queue;

    constructor() {
        super('QUEUE', true);
        this.queue = queue();
    }

    public insert(value: T, index?: number) {
        this.queue.enqueue(value);
    }

    public pop(value?: T): T {
        return this.queue.dequeue();
    }

    public search = null;
}

export default Queue;
