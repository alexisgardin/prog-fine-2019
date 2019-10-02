import BenchDataStructure from "../structures/BenchDataStructure";

class Benchmark {

    ds: BenchDataStructure<number>;

    constructor(dataStructure: BenchDataStructure<number>) {
        this.ds = dataStructure;
    }

    benchInsertion(insertFunc: (value: number) => void) {

    }

    runAll() {
        const insertion = this.ds.insert;
        const deletion = this.ds.pop;
        const research = this.ds.search;
    }
}

export default Benchmark;
