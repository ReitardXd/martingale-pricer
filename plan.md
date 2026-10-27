# Project plan

## 1. Goal and research question

`martingale-pricer` is a C++20 derivatives pricing engine that will price options independently with Monte Carlo (including variance reduction and quasi-Monte Carlo), a finite-difference PDE solver, and later Heston Fourier methods. It will compute Greeks with a hand-built adjoint algorithmic differentiation (AAD) tape and validate results against closed-form Black–Scholes formulas.

Research question: how much does quasi-Monte Carlo beat plain Monte Carlo as the effective dimension of a path-dependent payoff grows, and where does the advantage break down?

## 2. Ground rules

- [ ] Validate every component against a known answer before moving on.
- [ ] Always report standard errors or confidence intervals, never bare prices.
- [ ] Fix seeds. Do not use `std::normal_distribution` (its output is implementation-defined); implement the RNG and inverse-normal transform ourselves.
- [ ] Use double precision. Get single-threaded code correct before adding parallelism.
- [ ] Every module gets a derivation in `docs/theory/` and an experiment that confirms it.
- [ ] Do not report any performance or accuracy claim that has not been measured.

## 3. Phases

### Phase 0: Scaffolding, CI, sanitizers

- [ ] Establish the CMake project, source layout, and documentation.
- [ ] Add GCC and Clang CI builds and a passing smoke test.
- [ ] Exercise AddressSanitizer and UndefinedBehaviorSanitizer.

Deliverable: reproducible project skeleton with CI and sanitizer configuration.

Validation test: configure, build, run the smoke test, and run a sanitizer build.

Theory note: document build assumptions and sanitizer usage.

### Phase 1: Black-Scholes closed form for prices and Greeks; put-call parity tests

- [ ] Implement Black–Scholes prices and Greeks.
- [ ] Add put-call parity and limiting-case tests.

Deliverable: analytic reference implementation.

Validation test: compare prices and Greeks with hand-checked values and parity identities.

Theory note: derive the Black–Scholes PDE, solution, and Greeks.

### Phase 2: GBM model and plain Monte Carlo for European options

- [ ] Implement GBM paths and European payoffs.
- [ ] Report standard errors and confidence intervals.
- [ ] Verify N^(-1/2) convergence.
- [ ] Plot convergence on log-log axes.

Deliverable: statistically documented plain Monte Carlo engine.

Validation test: confidence intervals cover the analytic reference at a stated frequency; measured error follows the expected convergence trend.

Theory note: derive risk-neutral GBM simulation, estimator variance, and convergence rate.

### Phase 3: Variance reduction

- [ ] Add antithetic variates.
- [ ] Add control variates.
- [ ] Measure variance reduction with fixed seeds.

Deliverable: variance-reduced Monte Carlo experiments.

Validation test: compare estimators and confidence intervals with plain Monte Carlo on the same paths.

Theory note: derive the optimal control-variate coefficient.

### Phase 4: Sobol QMC and Brownian bridge construction

- [ ] Add Joe–Kuo Sobol direction numbers.
- [ ] Implement Brownian bridge construction.
- [ ] Compare MC and QMC on Asian and barrier options across effective dimensions.
- [ ] Measure where QMC advantage breaks down.

Deliverable: the experiment answering the research question.

Validation test: cross-check low-dimensional Sobol points and compare both methods with uncertainty reporting and reproducible seeds.

Theory note: derive Sobol mapping, Brownian bridge ordering, and effective dimension considerations.

### Phase 5: Crank-Nicolson PDE solver

- [ ] Implement a hand-written tridiagonal solver.
- [ ] Implement the Crank-Nicolson scheme.
- [ ] Measure empirical convergence order.

Deliverable: finite-difference European option solver.

Validation test: compare grid-refined prices with Black–Scholes and check boundary behavior.

Theory note: derive the scheme and include a von Neumann stability note.

### Phase 6: American options via Longstaff-Schwartz

- [ ] Implement regression-based continuation values.
- [ ] Add American payoffs and exercise diagnostics.

Deliverable: American option Monte Carlo engine.

Validation test: check against the PDE solver on matched contracts and tolerances.

Theory note: derive the optimal stopping and Longstaff-Schwartz regression procedure.

### Phase 7: AAD

- [ ] Write a reverse-mode tape.
- [ ] Support adjoint types needed by the pricing paths.
- [ ] Compare AAD Greeks with bump-and-revalue and closed-form Greeks.
- [ ] Measure the cost ratio.

Deliverable: validated hand-built AAD implementation.

Validation test: Greek differences stay within stated tolerances over a parameter grid.

Theory note: derive reverse-mode propagation and tape memory/cost trade-offs.

### Phase 8 (stretch): Heston

- [ ] Implement the characteristic function and Carr–Madan FFT.
- [ ] Add simulation with full truncation and QE schemes.

Deliverable: Heston Fourier and simulation pricers.

Validation test: cross-check against independent references and limiting Black–Scholes cases.

Theory note: derive the Heston characteristic function, FFT pricing, full truncation, and QE scheme.

### Phase 9: Portfolio polish

- [ ] Add a README with a hero convergence plot.
- [ ] Add a validation table.
- [ ] Benchmark against QuantLib.
- [ ] Write a one-page summary.

Deliverable: polished, reproducible portfolio project.

Validation test: clean checkout reproduces the documented builds, tests, figures, and measured results.

Theory note: document experiment methodology, uncertainty, and reproducibility.

## Results log

| Date | Experiment | Finding | File/plot |
|---|---|---|---|
|  |  |  |  |

## Reading list

- Shreve, *Stochastic Calculus for Finance I and II*
- Glasserman, *Monte Carlo Methods in Financial Engineering*
- Savine, *Modern Computational Finance: AAD and Parallel Simulations*
- Joshi, *C++ Design Patterns and Derivatives Pricing*
- Duffy, *Finite Difference Methods in Financial Engineering*
- Longstaff and Schwartz (2001)
- Giles and Glasserman, *Smoking Adjoints* (2006)

## Open questions

