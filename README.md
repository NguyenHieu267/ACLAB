# OpenVLA 
VLA pipeline for 7-DoF Franka robot from inference to simulation and testing using LIBERO/Robosuite.

[What is OpenVLA ?](https://openvla.github.io/)

[What is LIBERO ?](https://libero-project.github.io/main.html)

[What is Robosuite ?](https://robosuite.ai/)

## Requirements:
- Os: Ubuntu 24.04.4 LTS

- GPU: 3050 (8GB).

Note: >3050 is better. <br>
      You should install cuda for max performance.

## Setup Guide
### Setup conda:
```bash
# Update system 
sudo apt update && sudo apt upgrade -y

# Download Miniconda 
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh

# Run installer
bash Miniconda3-latest-Linux-x86_64.sh

# Activate Conda
source ~/miniconda3/bin/activate
```

### OpenVLA Installation
```bash
# Create and activate conda environment
conda create -n openvla python=3.10 -y
conda activate openvla

# Install PyTorch. Below is a sample command to do this, but you should check the following link
# to find installation instructions that are specific to your compute platform:
# https://pytorch.org/get-started/locally/
conda install pytorch torchvision torchaudio pytorch-cuda=12.4 -c pytorch -c nvidia -y  # UPDATE ME!
pip install torch torchvision torchaudio --upgrade         # UPDATE for OpenVLA compatibility

# Clone and install the openvla repo
git clone https://github.com/openvla/openvla.git
cd openvla
pip install -e .

# Install Flash Attention 2 for training (https://github.com/Dao-AILab/flash-attention)
#   =>> If you run into difficulty, try `pip cache remove flash_attn` first
pip install packaging ninja
ninja --version; echo $?  # Verify Ninja --> should return exit code "0"
pip install "flash-attn==2.5.5" --no-build-isolation
```
Remove TensorFlow dependencies from pyproject.toml to bypass strict version checks
```bash
sed -i '/tensorflow/d' pyproject.toml
sed -i '/dlimp/d' pyproject.toml
```

### Download Robotsuite:
```bash
# Create and activate environment
conda create -n robosuite python=3.10
conda activate robosuite

# Clone & Install
git clone https://github.com/ARISE-Initiative/robosuite.git
cd robosuite
pip3 install -r requirements-extra.txt
pip install -e .
```
#### 1) Check if mujuco == 3.10.0
```bash
pip uninstall mujoco
pip install mujoco==3.3.7
```

#### 2) Testing
```bash
python robosuite/demos/demo_random_action.py
```
#### 3) Return to home/root directory
```bash
cd ..
```

### Download LIBERO:
```bash
conda create -n libero python=3.8.13
conda activate libero
git clone https://github.com/Lifelong-Robot-Learning/LIBERO.git
cd LIBERO
conda install cmake -y
pip install -r requirements.txt
pip install torch==1.11.0+cu113 torchvision==0.12.0+cu113 torchaudio==0.11.0 --extra-index-url https://download.pytorch.org/whl/cu113
```

Install Dependency 
```bash
pip install tensorflow==2.13.0 --no-deps
pip install git+https://github.com/moojink/dlimp_openvla --no-deps
pip install tensorflow-datasets==4.9.2 --no-deps

pip install wrapt gast astunparse opt_einsum flatbuffers tree dm-tree tensorflow-metadata tensorflow-graphics
```
Optimize for 8GB VRAM
```bash
sed -i 's/"flash_attention_2"/"sdpa"/g' experiments/robot/openvla_utils.py
sed -i "s/'flash_attention_2'/'sdpa'/g" experiments/robot/openvla_utils.py
```

## How to run
#### 1) Fine-tuning Camera & Video Duration (Optional)
Before running the simulation, if you want the output video to be sharper and capture the robot's full range of motion, open the file `experiments/robot/libero/run_libero_eval.py` and modify the following three areas:
* **Increase resolution:** Locate the `get_libero_env` function (around line 140) and change the setting to `resolution=1024`.
* **Extend maximum duration:** Find the `max_steps` block (around line 151) and increase `libero_spatial` to 440 and `libero_object` to 560.
* **Prevent early video termination:** Locate the line `if done:` (around line 207) and add a `#` before the word `break` to disable it.
  
#### 2) Make sure you are inside the `openvla` directory and the `libero` conda environment is active. You can find the output video at `~/openvla/rollouts/`.
```bash
python experiments/robot/libero/run_libero_eval.py \
  --model_family openvla \
  --pretrained_checkpoint openvla/openvla-7b-finetuned-libero-spatial \
  --task_suite_name libero_spatial \
  --center_crop True \
  --load_in_4bit True
```
https://github.com/user-attachments/assets/c50db586-42d2-403f-9dd4-7b27e9de3c15

```bash
python experiments/robot/libero/run_libero_eval.py \
  --model_family openvla \
  --pretrained_checkpoint openvla/openvla-7b-finetuned-libero-object \
  --task_suite_name libero_object \
  --center_crop True \
  --load_in_4bit True \
  --num_trials_per_task 2
```
https://github.com/user-attachments/assets/ea5cac65-e06d-4513-ae2b-4df47fb5fca2
