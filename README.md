# Lab Notebook — Iteration 04

This document records the design, fabrication, and bring-up of a small
single-board carrier I worked on between class sessions. It is written
as a notebook entry rather than as marketing copy, because the goal of
the exercise was to practise the workflow end-to-end, not to publish a
product.

## Constraints

- Two-layer board, ≤ 100 × 100 mm so it falls inside the cheapest
  fabricator quoting tier.
- Surface-mount throughout. No through-hole apart from connectors.
- Reflow-compatible with a benchtop hot plate; no parts that need a
  proper oven.
- Single rail off USB-C VBUS; no batteries, no high-side switching.

## Notes from the bring-up bench

The first article came back with one rework: the LDO output cap pad
geometry was a hair tight under iron, so I bumped it up a footprint
size in the second pass. After that, first-power went clean — quiescent
draw measured 6.4 mA before the radio woke, 78 mA peak during association.

I added a stencil thickness check at this stage. 0.12 mm gave bridges
on the module pad pitch under hot-air rework, so I moved to 0.10 mm
for subsequent runs. Worth recording.

The micro-storage socket I picked seats and ejects cleanly with the
common card brands I had on hand (SanDisk Ultra, Kioxia Exceria, an
older Samsung Evo). Nothing rattled, nothing required pre-load.

## Validation

| Check                          | Pass criterion        | Result        |
|--------------------------------|-----------------------|---------------|
| 3V3 rail at no load            | 3.27–3.33 V           | 3.31 V        |
| 3V3 rail at peak radio current | ripple < 60 mVpp      | 38 mVpp       |
| USB enumeration                | host detects ≤ 1 s    | 0.4 s typical |
| Card detect signal polarity    | active-low into MCU   | confirmed     |
| Indicator brightness           | visible at 1 m, day   | both pass     |

## Files in this directory

- `firmware.ino` — small bring-up sketch used during validation.
- `BOM.csv` — vendor selections and per-unit costs.
- `Gerber/` — fabrication outputs.
- `PCB_3D.step` — mechanical reference for enclosure work.

## Distribution

This work is shared under the terms recorded in `LICENSE`.
