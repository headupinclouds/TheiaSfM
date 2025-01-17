.. _`chapter-applications`:

============
Applications
============

There are several applications that come with Theia right out of the box. These
applications are useful on their own, and also help provide context for how
Theia can be used for your own applications. Only minimal documentation is
provided here, but a full description of command line arguments and more can be
found within each application file.

Features
========

Extract Features
----------------

Extract any type of feature that is implemented in Theia (e.g., SIFT) and write
them to disk.

.. code-block:: bash

  ./bin/extract_features --input_images=/path/to/images/*.jpg --features_output_director=/path/to/output --num_threads=4 --descriptor=SIFT --logtostderr

Match Features
--------------

Given an input set of features (created with the extract_features program
above), this program will match descriptors between all images and optionally
perform geometric verification. Many parameters can be set at runtime, and the
match file is written out. This is useful for when you want to tune the matching parameters for performance without having to recompute all of the descriptors.

.. code-block:: bash

  ./bin/match_features --input_features=/path/to/features/*.features --output_matches_file=/path/to/output --num_threads=4 --matcher=CASCADE_HASHING --lowes_ratio=0.8 --logtostderr --v=1

Reconstructions
===============

Build Reconstruction
--------------------

This application will build a 3D reconstruction from a set of images or a set of
image matches. Detailed documentation for the structure-from-motion pipeline can
be found at :ref:`chapter-sfm`. Many parameters can be set at runtime (too many
to list here).

.. NOTE:: We provide an example of the possible command line flags for ``build_reconstructions`` in applications/build_reconstruction_flags.txt. We highly recommend that you copy this file then adjust the parameters for your own dataset and settings.

Once you have your flags file, you may create a 3D reconstruction by executing the command:

.. code-block:: bash

  ./bin/build_reconstruction --flagfile=/path/to/build_reconstruction_flags.txt

The reconstruction parameters may need to be tuned a bit for the individual datasets.

If images are supplied as input, then features are extracted and matched between
images before the reconstruction process begins. It is advised that you save
these matches (by specifying a --output_matches_file=/path/to/output.matches) so
that the reconstruction process may be restarted directly from the two-view
geometry. This allows you to tune the reconstruction parameters without having
to wait for image matching which is typically the slowest part of
structure-from-motion. Alternatively, you could first generate the two view
geometry and save the information using the program below.

1DSfM Dataset
-------------

The `1DSfM dataset <http://www.cs.cornell.edu/projects/1dsfm/>`_ is an excellent
dataset for SfM reconstructions from internet photo collections and is a
benchmark dataset for medium to large-scale SfM reconstructions. Since Theia is
aimed to make research and experimentation simple, we have provided an interface
to directly utilize the 1DSfM datasets without having to worry about processing
the data yourself.

.. NOTE:: We provide an example of the possible command line flags for ``build_1dsfm_reconstructions`` in applications/build_1dsfm_reconstruction_flags.txt. We highly recommend that you copy this file then adjust the parameters for your own dataset and settings.

By running the following command, you can utilize Theia's reconstruction
pipeline directly on the 1DSfM dataset:

.. code-block:: bash

   ./bin/build_1dsfm_reconstruction --flagfile=/path/to/build_1dsfm_reconstruction_flags.txt

Comparing Reconstructions
-------------------------

After computing SfM reconstructions, it can be useful to compare them. For
example, two reconstructions may be created with different parameters then
compared to determine how the various parameters affect reconstruction
quality. Running this program will output statistics such as rotation different,
positions difference, and the difference between camera intrinsic parameters.

.. code-block:: bash

   ./bin/compare_reconstructions --reconstruction1=ground_truth_reconstruction --reconstruction2=your_reconstruction --logtostderr

Note that reconstruction1 is considered the "ground truth" reconstruction for
this application. The reconstruction in reconstruction2 is aligned to
reconstruction1 with a similarity transformation (aligning the cameras with the
same name in both reconstructions) then the errors are measured.

For the 1DSfM dataset, you can use the ``compare_reconstructions`` application
to determine the ground truth errors. First, use the ``convert_bundle_file``
application to convert the ground truth Bundler files that come with the 1DSfM
dataset of interest. Then compare the reconstruction computed with Theia to the
ground truth reconstruction using the command line above. Since the ground truth
1DSfM bundler files are roughly metric-scale, the positions errors will be
approximately in meters.

Similarly, for the Strecha Dataset, you can first create a ground truth
reconstruction with the ``create_reconstruction_from_strecha_dataset``
program. Then use this as the ground truth reconstruction for
``compare_reconstructions``. Similar to the 1DSfM datasets, the ground truth
Strecha reconstructions are metric-scale and so are the position errors.

Compute Two View Geometry
-------------------------

Computes the two view matches and geometry between image pairs. This program
follows many of the same parameters as the Build Reconstructions program, but is
useful for generating two view geometries prior to building a
reconstruction. Feature matching is performed between images then geometric
verification is performed to determine which feature matches are inliers. Only
image pairs that have sufficiently many geometrically-verified matches are
considered valid.

Compute Reconstruction Statistics
---------------------------------

Computes some basic information about reconstructions such as reprojection
error, number of cameras, 3D points, and the average number of observations per
3D point.

.. code-block:: bash

   ./bin/compute_reconstruction_statistics --reconstruction=my_reconstruction --logtostderr

Compute Matching Relative Pose Errors
-------------------------------------

Two-view matches are the input to SfM, so the quality of the matches is
important to the final quality of the SfM reconstruction. To evaluate the
accuracy of various matching strategies (e.g., brute force vs cascade hashing,
or whether to perform two-view bundle adjustment), you can compare the input
two-view matches and geometry to the final reconstruction.

.. code-block:: bash

   ./bin/compute_matching_relative_pose_errors --matches=matches_file --reconstruction=ground_truth_reconstruction --logtostderr


View Reconstruction
-------------------

A very basic OpenGL point cloud viewer.

.. NOTE:: I am not an OpenGL expert so I welcome and encourage any improvements
          to the reconstruction viewer.

.. code-block:: bash

  ./bin/view_reconstruction --reconstruction=/path/to/theia/reconstruction

The reconstruction file can be generated using the :class:`ReconstructionWriter`.

The viewer currently displays all points with black, though in the future we may
record pixel color data. The cameras are displayed according to their intrinsic
parameters, so the size and shape of the camera wireframes is indicative of the
principal points, image width and height, and the focal length.

The controls are:

  ``LEFT MOUSE CLICK + DRAG``: Moves the position of the scene relative to the
  current viewpoint i.e., dragging left will move the scene to the left, etc.

  ``RIGHT MOUSE CLICK + DRAG``: Rotates the camera around the scene.

  ``MOUSE SCROLL UP or z``: Zooms the camera into the scene.

  ``MOUSE SCROLL DOWN or SHIFT + z``: Zooms the camera away from the scene.

  ``f``: Decreases the size of the cameras relative to the scene.

  ``SHIFT + f``: Increases the size of the cameras relative to the scene.

  ``p``: Decrease the size of the points in the point cloud (``NOTE``: there is
  a minimum size).

  ``P``: Increase the size of the points in the point cloud.

  ``c``: Toggle to choose whether to display or not display camera wireframes.

  ``t``: Increase the minimum number of views that must observe a 3D point in
  order for it to be displayed. By default, each 3D point must be observed by 2
  views in order to be displayed. Increasing this value will often result in a
  more clear reconstruction.

  ``T``: Decrease the minimum number of views that must observe a 3D point in
  order for it to be displayed.

Create Calibration File From EXIF
---------------------------------

Creates a calibration file from the EXIF information that can be
extracted from an image set.

Convert Bundle File
-------------------

Converts a bundler reconstruction to a Theia :class:`Reconstruction`.

Convert Sift Key File
---------------------

Converts Lowe's SIFT key files to a binary format.
