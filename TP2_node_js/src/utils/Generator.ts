
export const generateRandomList = (size: number, max: number): number[] => {
    return [...new Array(size)].map(() => Math.round(Math.random() * max));
};
