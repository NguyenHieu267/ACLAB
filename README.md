Os: Ubuntu 24.04.4 LTS

Setup conda:
1. Update system
$ sudo apt update && sudo apt upgrade -y

2. Download Miniconda
$ wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh

3. Run installer
$ bash Miniconda3-latest-Linux-x86_64.sh

4. Activate Conda
$ source ~/miniconda3/bin/activate

Download VSCode:
1. Download from vscode page
https://code.visualstudio.com/Download?_exp_download=fb315fc982

2. Run installer
$ sudo apt install ./<file_name>.deb

Download Robotsuite:
$ conda create -n robosuite python=3.10

$ conda activate robosuite

$ git clone https://github.com/ARISE-Initiative/robosuite.git
$ cd robosuite

$ pip3 install -r requirements-extra.txt

$ pip install -e .

1. Check if mujuco == 3.10.0
$ pip uninstall mujoco
$ pip install mujoco==3.3.7

2. Testing
$ python robosuite/demos/demo_random_action.py

Download Libero:
conda create -n libero python=3.8.13
conda activate libero
git clone https://github.com/Lifelong-Robot-Learning/LIBERO.git
cd LIBERO
conda install cmake -y
pip install -r requirements.txt
pip install torch==1.11.0+cu113 torchvision==0.12.0+cu113 torchaudio==0.11.0 --extra-index-url https://download.pytorch.org/whl/cu113

sed -i '/tensorflow/d' pyproject.toml
sed -i '/dlimp/d' pyproject.toml
pip install -e .

pip install tensorflow==2.13.0 --no-deps
pip install wrapt
pip install gast
pip install astunparse
pip install opt_einsum
pip install flatbuffers
pip install git+https://github.com/moojink/dlimp_openvla --no-deps
pip install tensorflow-datasets==4.9.2 --no-deps
pip install tree
pip install dm-tree
pip install tensorflow-metadata
pip install tensorflow-graphics
sed -i 's/"flash_attention_2"/"sdpa"/g' experiments/robot/openvla_utils.py
sed -i "s/'flash_attention_2'/'sdpa'/g" experiments/robot/openvla_utils.py


How to run

python experiments/robot/libero/run_libero_eval.py \
  --model_family openvla \
  --pretrained_checkpoint openvla/openvla-7b-finetuned-libero-spatial \
  --task_suite_name libero_spatial \
  --center_crop True \
  --load_in_4bit True

python experiments/robot/libero/run_libero_eval.py \
  --model_family openvla \
  --pretrained_checkpoint openvla/openvla-7b-finetuned-libero-object \
  --task_suite_name libero_object \
  --center_crop True \
  --load_in_4bit True \
  --num_trials_per_task 2
