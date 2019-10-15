function getNanoSecTime() {
    const hrTime = process.hrtime();
    return hrTime[0] * 1000000000 + hrTime[1];
}

class Timer {

    timer: number;

    public start(): void {
        this.timer = getNanoSecTime();
    }

    public stopAndGet(): number {
        return getNanoSecTime() - this.timer;
    }
}

export default Timer;
