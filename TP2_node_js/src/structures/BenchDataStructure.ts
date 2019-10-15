abstract class BenchDataStructure<T> {

    name: string;
    mutable: boolean;

    protected constructor(name = 'Generic Data Structure', mutable = false) {
        this.name = name;
        this.mutable = mutable;
    }

    insert(value: T, index?: number): void {
        throw new Error('Not implemented');
    }

    pop(value?: T): T {
        throw new Error('Not implemented');
    }

    search(value: T): T {
        throw new Error('Not implemented');
    }
}

export default BenchDataStructure;
