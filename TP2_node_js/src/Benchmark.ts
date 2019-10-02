import BenchDataStructure from "./BenchDataStructure";

class Benchmark {

    ds: BenchDataStructure<number>;

    constructor(dataStructure: BenchDataStructure<number>) {
        this.ds = dataStructure;
    }

    run() {

    }

    runAll() {
        const insertion = this.ds.insert;
        const deletion = this.ds.pop;
        const research = this.ds.search;
    }
}

export default Benchmark;
