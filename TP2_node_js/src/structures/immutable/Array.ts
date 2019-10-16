import BenchDataStructure from "../BenchDataStructure";
import { List } from "../custom/List/List";

class ImmutableArray<T> extends BenchDataStructure<T> {

    array: List;

    constructor() {
        super('ARRAY', false);
        this.array = new List();
    }

    public insert(value: any, index?: number) {
        this.array = this.array.set(index, value);
    }

    public pop(value?: any): any {
        return this.array.get(value);
    }

    public search = null;
}

export default ImmutableArray;
