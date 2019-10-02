abstract class BenchDataStructure<T> {

    name: string;
    mutable: boolean;

    protected constructor(name = 'Generic Data Structure', mutable = false) {
        this.name = name;
        this.mutable = mutable;
    }

    insert(value: T): void {
        // Void
    }

    pop(): T {
        return null;
    }

    search(value: T): T {
        return value;
    }
}

export default BenchDataStructure;
