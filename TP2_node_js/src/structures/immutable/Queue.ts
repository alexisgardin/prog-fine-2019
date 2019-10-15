import BenchDataStructure from "../BenchDataStructure";
import { ImmutableQueue } from "immutable-queue";
import * as ImQueue from "immutable-queue";

class Queue<T> extends BenchDataStructure<T> {

    queue: ImmutableQueue<T>;

    constructor() {
        super('QUEUE', false);
        this.queue = ImQueue.create<T>();
    }

    public insert(value: T, index?: number) {
        ImQueue.enqueue<T>(this.queue, value);
    }

    public pop(value?: T): any {
        return ImQueue.dequeue<T>(this.queue);
    }

    public search = null;
}

export default Queue;
