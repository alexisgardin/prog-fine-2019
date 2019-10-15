import BenchDataStructure from "../BenchDataStructure";

class MutableArray<T> extends BenchDataStructure<T> {

    array: Array<T>;

    constructor() {
        super('ARRAY', true);
        this.array = new Array<T>(100);
    }

    public insert(value: T, index?: number) {
        this.array[index] = value;
    }

    public pop(value?: T): T {
        return this.array[Number(value)];
    }

    public search = null;
}

export default MutableArray;
