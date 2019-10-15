import BenchDataStructure from "../BenchDataStructure";
import { Stack as ImmutableStack} from "immutable";

class Stack<T> extends BenchDataStructure<T> {

    stack: ImmutableStack<T>;

    constructor() {
        super('STACK', false);
        this.stack = ImmutableStack<T>();
    }

    public insert(value: T, index?: number) {
        this.stack = this.stack.push(value);
    }

    public pop(value?: T): T {
        const v = this.stack.peek();
        this.stack = this.stack.pop();
        return v;
    }

    public search = null;
}

export default Stack;
