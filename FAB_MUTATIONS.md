# Fab asset mutations for `submission_E_full_evasion`

## STEP aggressive multi-entity injection — fingerprint defeated

hard+: injected 4 mixed entities (CARTESIAN_POINT x2, DIRECTION, VERTEX_POINT) — entityCount, pointCount, AND types histogram all shift; bbox kept inside original envelope to avoid the dramatic bbox shift that submission_C produced

## Gerber per-layer mutation on every RS-274X layer — fingerprint defeated globally

hard+: per-layer canonical mutation on every RS-274X layer (10 layers: Gerber_BoardOutlineLayer.GKO, Gerber_BottomLayer.GBL, Gerber_BottomSilkscreenLayer.GBO, Gerber_BottomSolderMaskLayer.GBS, Gerber_DocumentLayer.GDL, Gerber_DrillDrawingLayer.GDD, Gerber_TopLayer.GTL, Gerber_TopPasteMaskLayer.GTP, Gerber_TopSilkscreenLayer.GTO, Gerber_TopSolderMaskLayer.GTS). Each layer's apertureSig list, apertureCount, and flashCount shift independently → no per-layer canonical match. Drill files (.DRL) are Excellon, not RS-274X, so the Gerber fingerprint doesn't apply to them anyway. | re-zipped into Gerber.zip — walker won't descend, archive blind spot stacks on top

## PCB auxiliary files (PDF/PNG/xlsx/.epro/.epcb) — all blob-SHA only, trivially defeated

trivial: PCB.epcb, PCB.epro, PCB.pdf, PickAndPlace_PCB.xlsx, Schematic.pdf, Schematic.png — all blob-SHA only at the detector (PDFs, PNGs, xlsx, .epro/.epcb have no structural fingerprint). Any byte change defeats. Mutations preserve viewer-loadability.
