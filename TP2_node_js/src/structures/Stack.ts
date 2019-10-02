import BenchDataStructure from "../BenchDataStructure";

class Stack<T> extends BenchDataStructure<T> {

    constructor() {
        super('Stack', false);
    }

    insert(value: T) {
        super.insert(value);
    }

    pop(): T {
        return super.pop();
    }

    search(value: T): T {
        return value;
    }
}

export default Stack;
