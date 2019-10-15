import BenchDataStructure from "../BenchDataStructure";
import { List } from "immutable";

class ImmutableArray<T> extends BenchDataStructure<T> {

    array: List<T>;

    constructor() {
        super('ARRAY', false);
        this.array = List<T>();
    }

    public insert(value: T, index?: number) {
        this.array = this.array.set(index, value);
    }

    public pop(value?: any): T {
        const v = this.array.get(value);
        this.array = this.array.remove(value);
        return v;
    }

    public search = null;
}

export default ImmutableArray;
