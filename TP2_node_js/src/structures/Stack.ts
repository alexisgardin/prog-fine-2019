import BenchDataStructure from "./BenchDataStructure";
import {stack} from "datastructures-js";

class Stack<T> extends BenchDataStructure<T> {

    stack: stack;

    constructor() {
        super('Stack', false);
    }

    insert(value: T) {
        this.stack.push(value);
    }

    pop(): T {
        return this.stack.pop();
    }
}

export default Stack;
