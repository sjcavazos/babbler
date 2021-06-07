[Mesh]
	type = GeneratedMesh # generates simple lines, rectangles and prisms
	dim = 2 # number of dimensions
	nx = 100  # number of elements in the x dir
	ny = 10 # number of elements in the y dir
	xmax = 0.304 # length of test chamber
	ymax = 0.0257 # test chamber radius
[]

[Problem]
	type = FEProblem # the "normal" type of Finite Element Problem in MOOSE
	coord_type = RZ # Axisymmetric RZ
	rz_coord_axis = X # the axis which the symmetry is round
[]

[Variables]
	[pressure]
		# adds a Linear Lagrange variable by default
	[]
[]

[Kernels]
	[diffusion]
		type = ADDiffusion # Laplacian operator
		variable = pressure # operating on the "pressure" variable
	[]
[]

[BCs]
	[inlet]
		type = ADDirichletBC # simple u=value BC
		variable = pressure # variable to be set
		boundary = left # name of thesideset in the mesh
		value = 4000 # (Pa) From Figure 2 in the paper. First data point for 1mm spheres
	[]
	[outlet]
		type = ADDirichletBC 
		variable = pressure
		boundary = right
		value = 0 # (Pa) Gives the correct pressure drop from Figure 2 for 1mm spheres
	[]
[]

[Executioner]
	type = Steady # steady state problem
	solve_type = 'NEWTON' # perform a Newton solve
	
	# Set PETSc parameters to optimize solver efficiency
	petsc_options_iname = '-pc_type -pc_hypre_type' # PETSc option pairs with values below
	petsc_options_value = ' hypre    boomeramg'
[]

[Outputs]
	exodus = true # Output Exodus format
[]
