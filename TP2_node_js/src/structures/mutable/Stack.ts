import BenchDataStructure from "../BenchDataStructure";
import {stack} from "datastructures-js";

class Stack<T> extends BenchDataStructure<T> {

    stack: stack;

    constructor() {
        super('STACK', true);
        this.stack = stack();
    }

    public insert(value: T, index?: number) {
        this.stack.push(value);
    }

    public pop(value?: T): T {
        return this.stack.pop();
    }

    public search = null;
}

export default Stack;
